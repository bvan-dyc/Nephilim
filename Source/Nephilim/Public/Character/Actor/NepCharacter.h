#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NepCharacter.generated.h"

UCLASS(config=Game)
class ANepCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	UPROPERTY(EditAnywhere)
	TArray<const class UNepCharacterMeshesDataAsset*> Set1;
	
	UPROPERTY(EditAnywhere)
	TArray<const class UNepCharacterMeshesDataAsset*> Set2;

	bool bFirstSet = true;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
public:
	
	ANepCharacter();

	template<typename T>
	T* GetConfig()
	{
		return FindComponentByClass<T>();
	}
	
	UFUNCTION(Server, Reliable)
	void Server_Interact(AActor* InteractableActor, int32 InteractionIndex);
	
protected:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Interact();

	template<int32 Index>
	void SelectInteraction()
	{
		SelectInteraction(Index);
	}

	void SelectInteraction(int32 Index);

	void ToggleUI();
	
	void Test();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	void MoveForward(float Value);
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

};

