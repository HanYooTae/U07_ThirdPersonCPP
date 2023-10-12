#include "CPlayerHealthWidget.h"
#include "Global.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Characters/CPlayer.h"
#include "Components/CStatusComponent.h"

void UCPlayerHealthWidget::NativeConstruct()
{
	CheckNull(CircleGuage);
	Material = CircleGuage->GetDynamicMaterial();
	CheckNull(Material);

	ACPlayer* player = Cast<ACPlayer>(GetOwningPlayer()->GetPawn());
	CheckNull(player);

	StatusComp = CHelpers::GetComponent<UCStatusComponent>(player);
	CheckNull(StatusComp);

	Material->SetScalarParameterValue("Ratio", StatusComp->GetCurrentHealth() / StatusComp->GetMaxHealth());

	CheckNull(CurrentHealthText);
	FString currentHealthStr = FString::FromInt((int32)StatusComp->GetCurrentHealth());
	CurrentHealthText->SetText(FText::FromString(currentHealthStr));
	
	Super::NativeConstruct();
}

void UCPlayerHealthWidget::UpdateHealth_Implementation()
{
	// 1. ���� �������� �پ�� ��
	CheckNull(Material);
	CheckNull(StatusComp);
	Material->SetScalarParameterValue("Ratio", StatusComp->GetCurrentHealth() / StatusComp->GetMaxHealth());


	// 2. �ؽ�Ʈ�� ���� ü������ ǥ�õǾ�� ��
	CheckNull(CurrentHealthText);
	FString currentHealthStr = FString::FromInt((int32)StatusComp->GetCurrentHealth());
	CurrentHealthText->SetText(FText::FromString(currentHealthStr));

	PlayAnimationForward(DecreaseImpact);
}