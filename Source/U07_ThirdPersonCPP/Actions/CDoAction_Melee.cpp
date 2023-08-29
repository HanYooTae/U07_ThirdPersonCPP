#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();

	// 액션(공격) 몽타주 재생
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	// 노티파이 비긴(콤보 : 넥스트 콤보, 매직볼 : 스폰 프로젝타일...)
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	// 노티파이 엔드(아이들 상태, 캔부므 풀어주는 등)
}
