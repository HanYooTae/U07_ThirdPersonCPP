#include "CBTService_Melee.h"
#include "Actions/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CPatrolComponent.h"
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

	// 플레이어가 감지되었을 때 or 감지가 안되었을 때
	// 감지가 되었을 때 거리에 따라서 BehaviorComp->SetOOOMode
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	ACEnemy_AI* enemy = Cast<ACEnemy_AI>(controller->GetPawn());
	CheckNull(enemy);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(enemy);
	CheckNull(stateComp);

	UCPatrolComponent* patrolComp = CHelpers::GetComponent<UCPatrolComponent>(enemy);
	CheckNull(patrolComp);

	// Hitted
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
		if (patrolComp->IsPathValid())
		{
			behaviorComp->SetPatrolMode();
			return;
		}

		behaviorComp->SetWaitMode();
		return;
	}

	// Perceived Player Dead
	UCStateComponent* playerStateComp = CHelpers::GetComponent<UCStateComponent>(player);
	if (!!playerStateComp)
	{
		if (playerStateComp->IsDeadMode())
		{
			behaviorComp->SetWaitMode();
			return;
		}
	}

	// Player exist
	float distance = enemy->GetDistanceTo(player);

	//-> Is in Attack Range(150)
	if (distance < controller->GetBehaviorRange())
	{
		behaviorComp->SetActionMode();
		return;
	}

	//-> Is in Sight Range(600)
	if (distance < controller->GetSightRadius())
	{
		behaviorComp->SetApproachMode();
		return;
	}
}