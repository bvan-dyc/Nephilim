#include "Character/Actor/NepCharacter.h"
#include "ArcECSSubsystem.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Character/ActorComponent/NepCharacterComponent.h"
#include "Character/Resource/NepCharacterEvents.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Field/FieldSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Interaction/Actor/NepLongInteractionProxy.h"
#include "Interaction/Component/NepInteractable.h"
#include "Interaction/Component/NepInteractor.h"
#include "Interaction/Resource/NepInteractionEvents.h"
#include "Interaction/Resource/NepServerInteractionData.h"

ANepCharacter::ANepCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ANepCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ANepCharacter::Interact);
	PlayerInputComponent->BindAction("SelectInteraction_1", IE_Pressed, this, &ANepCharacter::SelectInteraction<0>);
	PlayerInputComponent->BindAction("SelectInteraction_2", IE_Pressed, this, &ANepCharacter::SelectInteraction<1>);
	PlayerInputComponent->BindAction("SelectInteraction_3", IE_Pressed, this, &ANepCharacter::SelectInteraction<2>);
	PlayerInputComponent->BindAction("SelectInteraction_4", IE_Pressed, this, &ANepCharacter::SelectInteraction<3>);
	PlayerInputComponent->BindAction("SelectInteraction_5", IE_Pressed, this, &ANepCharacter::SelectInteraction<4>);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAction("ToggleUI", IE_Pressed, this, &ANepCharacter::ToggleUI);
	PlayerInputComponent->BindAction("Test", IE_Pressed, this, &ANepCharacter::Test);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANepCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANepCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ANepCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ANepCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ANepCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ANepCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ANepCharacter::OnResetVR);
}

void ANepCharacter::Interact()
{
	UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	if (FNepInteractionEvents* Events = Universe ? Universe->GetResource<FNepInteractionEvents>() : nullptr)
	{
		Events->bInteractionKeyPressed = true;
	}
}

void ANepCharacter::Server_Interact_Implementation(AActor* InteractableActor, int32 InteractionIndex)
{
	if (!InteractableActor || FVector::DistSquared2D(GetActorLocation(), InteractableActor->GetActorLocation()) > FMath::Square(300.0f)) { return; }
	UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	UWorld* World = GetWorld();
	if (!Universe || !World) { return; }

    FArcEntityHandle* InteractingEntity = ECSSubsystem->FindEntityForActor(*this);
	FArcEntityHandle* InteractableEntity = ECSSubsystem->FindEntityForActor(*InteractableActor);
	if (!InteractingEntity || !InteractableEntity) { return; }
	
	FNepInteractor* Interactor = InteractingEntity ? Universe->GetComponent<FNepInteractor>(*InteractingEntity) : nullptr;

	FNepInteractable* Interactable = InteractableEntity ? Universe->GetComponent<FNepInteractable>(*InteractableEntity) : nullptr;
	FNepInteraction* Interaction =
		Interactable && Interactable->Interactions.IsValidIndex(InteractionIndex) ?
		Interactable->Interactions[InteractionIndex].Get() :
		nullptr;

	FNepServerInteractionData* ServerInteractionData = Universe->GetResource<FNepServerInteractionData>();
	TSubclassOf<ANepLongInteractionProxy> ProxyClass = Interaction->GetLongInteractionProxyClass();
	if (ServerInteractionData && ProxyClass)
	{
		ANepLongInteractionProxy* Proxy = World->SpawnActor<ANepLongInteractionProxy>(ProxyClass);
		Proxy->InitializeProxy(*this, *InteractableActor);
		Proxy->SetOwner(this);
		Proxy->CopyRemoteRoleFrom(this);
		Proxy->InteractorActor = this;
		Proxy->InteractableActor = InteractableActor;
		Interactor->InteractionProxies.Add(Proxy);
		ServerInteractionData->InteractionProxies.Add(Proxy);
	}

	FNepInteractionEvents* Events = Universe->GetResource<FNepInteractionEvents>();
	if (Interaction && Interaction->IsInteractionPossibleOnServer(*Universe, *InteractingEntity, *InteractableEntity) && Events)
	{
		Interaction->ExecuteOnServer(*InteractingEntity, *InteractableEntity, *Events);
	}
}

void ANepCharacter::SelectInteraction(int32 Index)
{
	UArcECSSubsystem* ECSSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = ECSSubsystem ? &ECSSubsystem->GetUniverse() : nullptr;
	if (FNepInteractionEvents* Events = Universe ? Universe->GetResource<FNepInteractionEvents>() : nullptr)
	{
		Events->SelectedInteractionIndex = Index;
	}
}

void ANepCharacter::ToggleUI()
{
	UArcECSSubsystem* CoreSubsystem = UWorld::GetSubsystem<UArcECSSubsystem>(GetWorld());
	FArcUniverse* Universe = CoreSubsystem ? &CoreSubsystem->GetUniverse() : nullptr;
	if (FNepCharacterEvents* Events = Universe ? Universe->GetResource<FNepCharacterEvents>() : nullptr)
	{
		Events->bToggleUI = true;
	}
}

void ANepCharacter::Test()
{
	if (UNepCharacterComponent* CharacterConfig = GetConfig<UNepCharacterComponent>())
	{
		bFirstSet = !bFirstSet;
		CharacterConfig->Server_RemoveMeshes();
		TArray<const UNepCharacterMeshesDataAsset*>& Set = bFirstSet ? Set1 : Set2;
		for (const UNepCharacterMeshesDataAsset* Meshes : Set)
		{
			CharacterConfig->Server_SetMeshes(Meshes);
		}
	}
}

void ANepCharacter::OnResetVR()
{
	// If NephilimTest is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in NephilimTest.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ANepCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ANepCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ANepCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ANepCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ANepCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ANepCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
