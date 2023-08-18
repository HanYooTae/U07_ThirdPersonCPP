#include "U07_ThirdPersonCPPGameModeBase.h"
#include "Global.h"

AU07_ThirdPersonCPPGameModeBase::AU07_ThirdPersonCPPGameModeBase()
{
	CHelpers::GetClass(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
}