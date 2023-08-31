#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHealthWidget.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API UCHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
		void UpdateHealth(float InCurrentHP, float InMaxHP);
		void UpdateHealth_Implementation(float InCurrentHP, float InMaxHP);

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
};
