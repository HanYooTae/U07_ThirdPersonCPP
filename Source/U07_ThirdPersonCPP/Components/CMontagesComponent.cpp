#include "CMontagesComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCMontagesComponent::UCMontagesComponent()
{

}


void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr)
	{
		CLog::Log("DataTable is not set");
		return;
	}

	TArray<FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	for (const auto& data : datas)
	{
		CLog::Log(data->AnimMontage->GetName() + ", " + FString::SanitizeFloat(data->PlayRate));
	}

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (const auto& data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;

				break;
			}
		}
	}
}

void UCMontagesComponent::PlayRoll()
{
	PlayAnimMontage(EStateType::Roll);
}

void UCMontagesComponent::PlayBackStep()
{
	PlayAnimMontage(EStateType::BackStep);
}

void UCMontagesComponent::PlayHitted()
{
	PlayAnimMontage(EStateType::Hitted);
}

void UCMontagesComponent::PlayDead()
{
	PlayAnimMontage(EStateType::Dead);
}

void UCMontagesComponent::PlayAnimMontage(EStateType InStateType)
{

	//CLog::Print(FString::FromInt((int32)InStateType));
	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(ownerCharacter);


	const FMontageData* data = Datas[(int32)InStateType];
	//CLog::Log(!!data ? "NotNull" : "Null");

	if(!!data && !!data->AnimMontage)
		ownerCharacter->PlayAnimMontage(data->AnimMontage, data->PlayRate, data->StartSection);
}
