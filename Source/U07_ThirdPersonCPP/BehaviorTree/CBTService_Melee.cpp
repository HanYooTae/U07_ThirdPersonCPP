#include "CBTService_Melee.h"
#include "Actions/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Characters/CAIController.h"
#include "Characters/CPlayer.h"
#include "Characters/CEnemy_AI.h"
#include "Global.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Melee";
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// �÷��̾ �����Ǿ��� �� or ������ �ȵǾ��� ��
	// ������ �Ǿ��� �� �Ÿ��� ���� BehaviorComp->SetOOOMode
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	ACEnemy_AI* enemy = Cast<ACEnemy_AI>(controller->GetPawn());
	CheckNull(enemy);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(enemy);
	CheckNull(stateComp);

	if (stateComp->IsHittedMode())
	{
		behaviorComp->SetHittedMode();
		return;
	}

	// Perceived Player(Get Player from BB)
	ACPlayer* player = behaviorComp->GetPlayerKey();

	// No Player
	if (player == nullptr)
	{
		behaviorComp->SetWaitMode();
		return;
	}

	// Player exist
	float distance = enemy->GetDistanceTo(player);

	behaviorComp->SetApproachMode();
	behaviorComp->SetActionMode();
}