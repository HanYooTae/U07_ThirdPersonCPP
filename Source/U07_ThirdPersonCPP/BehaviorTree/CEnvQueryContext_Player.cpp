#include "CEnvQueryContext_Player.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CAIController.h"
#include "Characters/CPlayer.h"
#include "Actions/CBehaviorComponent.h"

void UCEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);
	
	// QueryInstance : EQS_Avoid Asset
	// QueryInstance.Owner = ACEnemy_Magic

	// BB
	ACEnemy_AI* enemy = Cast<ACEnemy_AI>(QueryInstance.Owner.Get());
	CheckNull(enemy);

	ACAIController* controller = Cast<ACAIController>(enemy->GetController());
	CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, behaviorComp->GetPlayerKey());
}