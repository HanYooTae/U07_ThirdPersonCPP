#include "CAnimInstance.h"
#include "Global.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* owerPawn = TryGetPawnOwner();
	CheckNull(owerPawn);
	
	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(owerPawn);
	CheckNull(actionComp);

	actionComp->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* owerPawn = TryGetPawnOwner();
	CheckNull(owerPawn);

	Speed = owerPawn->GetVelocity().Size2D();
	Direction = CalculateDirection(owerPawn->GetVelocity(), owerPawn->GetControlRotation());
	UCFeetComponent* feetComp = CHelpers::GetComponent<UCFeetComponent>(owerPawn);
	CheckNull(feetComp);

	FeetData = feetComp->GetData();
}

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}
