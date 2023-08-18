#include "CAnimInstance.h"
#include "Global.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* owerPawn = TryGetPawnOwner();
	CheckNull(owerPawn);

	Speed = owerPawn->GetVelocity().Size2D();
	Direction = CalculateDirection(owerPawn->GetVelocity(), owerPawn->GetControlRotation());
}