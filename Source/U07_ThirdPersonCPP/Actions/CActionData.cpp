#include "CActionData.h"
#include "CEquipment.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"
#include "Global.h"

void UCActionData::BeginPlay(class ACharacter* InOwnerCharacter)
{
	FTransform transform;

	if (!!AttachmentClass)
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, transform, InOwnerCharacter);
		Attachment->SetActorLabel(GetCustomActorLabel(InOwnerCharacter, "Attachment"));
		UGameplayStatics::FinishSpawningActor(Attachment, transform);
	}

	if (!!EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, transform, InOwnerCharacter);

		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(GetCustomActorLabel(InOwnerCharacter, "Equipment"));

		UGameplayStatics::FinishSpawningActor(Equipment, transform);

		if (!!Attachment)
		{
			Equipment->OnBeginEquip.AddDynamic(Attachment, &ACAttachment::OnEquip);
			Equipment->OnUnequip.AddDynamic(Attachment, &ACAttachment::OnUnequip);
		}
	}

	if (!!DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, transform, InOwnerCharacter);

		DoAction->SetDatas(DoActionDatas);
		DoAction->SetActorLabel(GetCustomActorLabel(InOwnerCharacter, "DoAction"));

		UGameplayStatics::FinishSpawningActor(DoAction, transform);
	}
}

FString UCActionData::GetCustomActorLabel(class ACharacter* InOwnerCharacter, FString InMiddleName)
{
	FString name;
	name.Append(InOwnerCharacter->GetActorLabel());
	name.Append("_");
	name.Append(InMiddleName);
	name.Append("_");

	name.Append(GetName().Replace(L"DA_", L""));

	return name;
}
