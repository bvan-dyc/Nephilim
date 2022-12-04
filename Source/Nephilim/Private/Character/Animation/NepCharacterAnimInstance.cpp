#include "Character/Animation/NepCharacterAnimInstance.h"

void UNepCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    AActor* Owner = GetOwningActor();
    if (!Owner) { return; }

    //Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());

    Speed = Owner->GetVelocity().Size();

    //bDash = false;
}
