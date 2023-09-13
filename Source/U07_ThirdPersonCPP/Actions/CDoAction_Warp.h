#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Warp.generated.h"

UCLASS()
class U07_THIRDPERSONCPP_API ACDoAction_Warp : public ACDoAction
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void DoAction() override;		// Play Warp Montage
	virtual void Begin_DoAction() override;	// Play Particle
	virtual void End_DoAction() override;	// Jump to Cursor Location
};
