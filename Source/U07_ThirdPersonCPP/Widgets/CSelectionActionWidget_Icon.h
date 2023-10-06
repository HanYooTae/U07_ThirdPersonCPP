#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSelectionActionWidget_Icon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FImageButtonPressedSignature);

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

public:
	void SetTextureToImageButton(class UTexture2D* InImage);

public:
	UPROPERTY(BlueprintAssignable)
		FImageButtonPressedSignature OnImageButtonPressed;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* ImageButton;
};
