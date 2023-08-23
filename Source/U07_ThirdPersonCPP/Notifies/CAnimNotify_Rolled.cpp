#include "CAnimNotify_Rolled.h"
#include "Characters/CPlayer.h"
#include "Global.h"

FString UCAnimNotify_Rolled::GetNotifyName_Implementation() const
{
	return "Rolled";
}

void UCAnimNotify_Rolled::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player =  Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	player->End_Roll();
}
