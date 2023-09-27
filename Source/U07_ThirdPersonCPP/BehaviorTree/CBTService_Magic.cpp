#include "CBTService_Magic.h"
#include "Actions/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Characters/CAIController.h"
#include "Characters/CPlayer.h"
#include "Characters/CEnemy_AI.h"
#include "Global.h"

UCBTService_Magic::UCBTService_Magic()
{
	NodeName = "Magic";
}

void UCBTService_Magic::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	ACEnemy_AI* enemy = Cast<ACEnemy_AI>(controller->GetPawn());
	CheckNull(enemy);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(enemy);
	CheckNull(stateComp);

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
		behaviorComp->SetWaitMode();
		controller->ClearFocus(EAIFocusPriority::Gameplay);
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
	controller->SetFocus(player);

	//-> Is in Avoid Range(400)
	if (distance < controller->GetBehaviorRange())
	{
		behaviorComp->SetAvoidMode();
		return;
	}

	//-> Is in Attack Range(1000)
	if (distance < controller->GetSightRadius())
	{
		behaviorComp->SetActionMode();
		return;
	}
}
