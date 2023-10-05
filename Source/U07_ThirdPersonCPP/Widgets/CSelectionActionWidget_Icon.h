#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSelectionActionWidget_Icon.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API UCSelectionActionWidget_Icon : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
		void OnPressed();

	UFUNCTION(BlueprintCallable)
		void OnHover();

	UFUNCTION(BlueprintCallable)
		void OnUnHover();

private:
	class UCSelectAcionWidget_Group* GetParentWidget();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* ImageButton;
};
