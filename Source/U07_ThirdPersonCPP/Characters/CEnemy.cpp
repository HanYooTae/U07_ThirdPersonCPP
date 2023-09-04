#include "CEnemy.h"
#include "Global.h"
#include "Components/CActionComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CMontagesComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Widgets/CNameWidget.h"
#include "Widgets/CHealthWidget.h"

ACEnemy::ACEnemy()
{
	// Create Scene Component
	// -> MeshComponent
	CHelpers::CreateSceneComponent(this, &NameWidget, "NameWidget", GetMesh());
	CHelpers::CreateSceneComponent(this, &HealthWidget, "HealthWidget", GetMesh());

	// Create Actor Component
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Status, "Status");

	// Component Settings
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "SkeletalMesh'/Game/Character/ZLorp/Mesh/ZLorp.ZLorp'");
	GetMesh()->SetSkeletalMesh(meshAsset);

	TSubclassOf<UAnimInstance> animInstanceClass;
	CHelpers::GetClass(&animInstanceClass, "AnimBlueprint'/Game/Enemies/ABP_CEnemy.ABP_CEnemy_C'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);

	// -> MovementComp
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->MaxWalkSpeed = Status->GetRunSpeed();

	// -> WidgetComp
	TSubclassOf<UCNameWidget> nameWidgetClass;
	CHelpers::GetClass(&nameWidgetClass, "WidgetBlueprint'/Game/Widget/WB_Name.WB_Name_C'");
	NameWidget->SetWidgetClass(nameWidgetClass);
	NameWidget->SetRelativeLocation(FVector(0, 0, 220));
	NameWidget->SetDrawSize(FVector2D(240, 50));
	NameWidget->SetWidgetSpace(EWidgetSpace::Screen);

	TSubclassOf<UCHealthWidget> healthWidgetClass;
	CHelpers::GetClass(&healthWidgetClass, "WidgetBlueprint'/Game/Widget/WB_Health.WB_Health_C'");
	HealthWidget->SetWidgetClass(healthWidgetClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 180));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACEnemy::BeginPlay()
{
	// Create Dynamic Material
	LowerMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	UpperMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);

	GetMesh()->SetMaterial(0, LowerMaterial);
	GetMesh()->SetMaterial(1, UpperMaterial);

	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);

	Super::BeginPlay();
	

	NameWidget->InitWidget();
	UCNameWidget* nameWidget = Cast<UCNameWidget>(NameWidget->GetUserWidgetObject());
	if (!!nameWidget)
	{
		nameWidget->SetNames(GetController()->GetName(), GetName());
	}

	HealthWidget->InitWidget();
	UCHealthWidget* healthWidget = Cast<UCHealthWidget>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidget)
	{
		healthWidget->UpdateHealth(Status->GetCurrentHealth(), Status->GetMaxHealth());
	}

}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	Causer = DamageCauser;

	Status->DecreaseHealth(DamageValue);

	if (Status->IsDead())
	{
		State->SetDeadMode();
		return DamageValue;
	}
	State->SetHittedMode();

	return DamageValue;
}

void ACEnemy::ChangeBodyColor(FLinearColor InColor)
{
	if (State->IsHittedMode())
	{
		LowerMaterial->SetVectorParameterValue("BodyColor", InColor);
		UpperMaterial->SetVectorParameterValue("BodyColor", InColor);

		return;
	}
}

void ACEnemy::RestoreColor()
{
	LowerMaterial->SetVectorParameterValue("BodyColor", FLinearColor::Black);
	UpperMaterial->SetVectorParameterValue("BodyColor", FLinearColor::Black);
}

void ACEnemy::Hitted()
{
	// Apply Health Widget
	UCHealthWidget* healthWidget = Cast<UCHealthWidget>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidget)
	{
		healthWidget->UpdateHealth(Status->GetCurrentHealth(), Status->GetMaxHealth());
	}

	// Play Hitted Montage
	Montages->PlayHitted();

	// Look At Attacker
	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FRotator rotation = FRotator(0, UKismetMathLibrary::FindLookAtRotation(start, target).Yaw, 0);
	SetActorRotation(rotation);

	// HitBack
	FVector direction = (start - target).GetSafeNormal();
	LaunchCharacter(direction * LaunchValue * DamageValue, true, false);

	// Change Hit Color
	ChangeBodyColor(FLinearColor::Red);

	UKismetSystemLibrary::K2_SetTimer(this, "RestoreColor", 0.5f, false);
}

void ACEnemy::Dead()
{
	// Widget Visibility Disabled
	NameWidget->SetVisibility(false);
	HealthWidget->SetVisibility(false);

	// Ragdoll
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->GlobalAnimRateScale = 0.f;

	// Add Force
	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FVector direction = (start = target).GetSafeNormal();
	FVector force = direction * LaunchValue * DamageValue;
	GetMesh()->AddForceAtLocation(force, start);

	// Destroy All(Attachment, Equipment, DoAction...);

}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Hitted: Hitted();	break;
	case EStateType::Dead:	 Dead();	break;
	}
}
