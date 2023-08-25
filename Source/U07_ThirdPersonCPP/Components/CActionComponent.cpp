#include "CActionComponent.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"
#include "GameFramework/Character.h"

UCActionComponent::UCActionComponent()
{
}



void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if(!!Datas[i])
			Datas[i]->BeginPlay(ownerCharacter);
	}
}

void UCActionComponent::SetUnarmedMode()
{
	if(!!Datas[(int32)Type] && !!Datas[(int32)Type]->GetEquipment())
		Datas[(int32)Type]->GetEquipment()->UnEquip();

	Datas[(int32)EActionType::Unarmed]->GetEquipment()->Equip();

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void UCActionComponent::SetMagicBallMode()
{
	SetMode(EActionType::MagicBall);
}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetStormMode()
{
	SetMode(EActionType::Storm);
}

void UCActionComponent::SetMode(EActionType InNewType)
{
	// ���� Ű�� 2�������� ��
	if (Type == InNewType)
	{
		SetUnarmedMode();

		return;
	}

	// �ٸ� ���� ��ü

	ChangeType(InNewType);
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prev, InNewType);
}