#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSelectAcionWidget_Group.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API UCSelectAcionWidget_Group : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
		void Pressed(FString InName);

	UFUNCTION(BlueprintCallable)
		void Hover(FString InName);

	UFUNCTION(BlueprintCallable)
		void Unhover(FString InName);

public:
	FORCEINLINE class UCSelectionActionWidget_Icon* GetChildWidget(FString InName) { return IconWidgets[InName]; }

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<UTexture2D*> Images;

	UPROPERTY(BlueprintReadOnly)
		TMap<FString, class UCSelectionActionWidget_Icon*> IconWidgets;

private:
	UPROPERTY(meta = (BindWidget))
		class UGridPanel* Grid;
};
