#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Melee.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()

public:
	void DoAction() override;

	void Begin_DoAction() override;
	void End_DoAction() override;

	virtual void OnBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;
	virtual void OnEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) override;

	FORCEINLINE void EnableCombo() { bCanCombo = true; }
	FORCEINLINE void DisableCombo() { bCanCombo = false; }
	FORCEINLINE void ClearHittedCharacters() { HittedCharacters.Empty(); }

private:
	UFUNCTION()
		void RestoreTimeDilation();

private:
	int32 ComboCount;
	bool bCanCombo;
	bool bSucceed;

	TArray<class ACharacter*> HittedCharacters;
};
