#include "CAIController.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Actions/CBehaviorComponent.h"
#include "CEnemy_AI.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "CPlayer.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	// Todo. (0)Use BlackBoard (1)Run BT, (2)PerceptionComp
	CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent(this, &Behavior, "Behavior");
	CHelpers::CreateActorComponent(this, &Perception, "Perception");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 600.f;
	Sight->LoseSightRadius = 800.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;
	Sight->SetMaxAge(2.f);
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(Sight->GetSenseImplementation());
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedEnemy = Cast<ACEnemy_AI>(InPawn);
	UseBlackboard(PossessedEnemy->GetBehaviorTree()->BlackboardAsset, Blackboard);

	SetGenericTeamId(PossessedEnemy->GetTeamID());
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(PossessedEnemy->GetBehaviorTree());

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();
}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ACAIController::GetSightRadius()
{
	return Sight->SightRadius;
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);
	
	ACPlayer* player = nullptr;

	for (const auto& perceivedActor : actors)
	{
		player = Cast<ACPlayer>(perceivedActor);

		if (!!player)
			break;
	}

	Blackboard->SetValueAsObject("PlayerKey", player);
}
