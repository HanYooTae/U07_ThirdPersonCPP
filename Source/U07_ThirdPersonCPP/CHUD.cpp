#include "CHUD.h"
#include "Global.h"
#include "Engine/Canvas.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* playerCharacter =  UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	CheckNull(playerCharacter);

	StateComp = CHelpers::GetComponent<UCStateComponent>(playerCharacter);
	CheckNull(StateComp);

	StateTypeEnum = FindObject<UEnum>(ANY_PACKAGE, L"EStateType", true);
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();

	CheckNull(StateComp);
	CheckNull(StateTypeEnum);

	FString typeStr = StateTypeEnum->GetNameStringByValue((int64)StateComp->GetType());

	DrawText(typeStr, FLinearColor::Red, 10, Canvas->ClipY - 50, nullptr, 1.5f);

	StateComp->GetType();

}