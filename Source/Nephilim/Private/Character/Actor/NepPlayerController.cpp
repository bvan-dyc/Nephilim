#include "Character/Actor/NepPlayerController.h"
#include "Character/ActorComponent/NepPlayerInputComponent.h"
#include "UI/Widget/NepHUDWidget.h"

void ANepPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UNepPlayerInputComponent* PlayerInputComponent = NewObject<UNepPlayerInputComponent>(this, UNepPlayerInputComponent::StaticClass());
    PlayerInputComponent->SetupBindings();
    PlayerInputComponent->RegisterComponent();
    PushInputComponent(PlayerInputComponent);
}
