#include "CBTTaskNode_Action.h"
#include "Global.h"
#include "Characters/CEnemy.h"
#include "AIController.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
	NodeName = "Action";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// OwnerCharacter->ActionComp
	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACEnemy* enemy = Cast<ACEnemy>(controller->GetPawn());
	CheckNullResult(enemy, EBTNodeResult::Failed);

	UCActionComponent* actionComp = CHelpers::GetComponent<UCActionComponent>(enemy);
	CheckNullResult(actionComp, EBTNodeResult::Failed);

	actionComp->DoAction();

	RunningTime = 0.f;

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 상태가 Idle이면서 2초가 경과했다면 성공 리턴
	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNull(controller);

	ACEnemy* enemy = Cast<ACEnemy>(controller->GetPawn());
	CheckNull(enemy);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(enemy);
	CheckNull(stateComp);

	RunningTime += DeltaSeconds;

	if (stateComp->IsIdleMode() && RunningTime >= Delay)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
