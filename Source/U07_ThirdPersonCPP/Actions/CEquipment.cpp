#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Characters/ICharacter.h"

ACEquipment::ACEquipment()
{

}

void ACEquipment::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	StateComp = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	StatusComp = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
}

void ACEquipment::Equip_Implementation()
{
	// Set State Equip
	StateComp->SetEquipMode();

	// bCanMove
	Data.bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();

	// Play Draw AnimMontage
	if (!!Data.AnimMontage)
	{
		//CLog::Print(Data.AnimMontage->GetName());
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRate, Data.StartSection);
	}
	else
	{
		Begin_Equip();
		End_Equip();
	}

	// bPawnController
	if (Data.bPawnControl == true)
	{
		OwnerCharacter->bUseControllerRotationYaw = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	// Change Color
	IICharacter* characterInterface = Cast<IICharacter>(OwnerCharacter);
	CheckNull(characterInterface);
	characterInterface->ChangeBodyColor(Color);
}

void ACEquipment::Begin_Equip_Implementation()
{
	if (OnBeginEquip.IsBound())
		OnBeginEquip.Broadcast();
}

void ACEquipment::End_Equip_Implementation()
{
	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ACEquipment::Unequip_Implementation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	if (OnUnequip.IsBound())
		OnUnequip.Broadcast();
}
