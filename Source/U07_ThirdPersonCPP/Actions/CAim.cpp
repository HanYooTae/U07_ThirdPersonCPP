#include "CAim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


UCAim::UCAim()
{
	CHelpers::GetAsset(&Curve, "CurveFloat'/Game/Player/Curve_Aim.Curve_Aim'");
}

void UCAim::BeginPlay(ACharacter* InOwnerCharacter)
{
	OwnerCharacter = InOwnerCharacter;

	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	OnTimeline.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, OnTimeline);
	Timeline.SetPlayRate(5.f);
}

void UCAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UCAim::On()
{
	CheckFalse(IsAvailable());
	CheckTrue(bZooming);
	bZooming = true;

	SpringArm->TargetArmLength = 100;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	SpringArm->bEnableCameraLag = false;

	Timeline.PlayFromStart();
}

void UCAim::Off()
{
	CheckFalse(IsAvailable());
	CheckFalse(bZooming);
	bZooming = false;

	SpringArm->TargetArmLength = 200;
	SpringArm->SocketOffset = FVector::ZeroVector;
	SpringArm->bEnableCameraLag = true;

	Timeline.ReverseFromEnd();
}

void UCAim::Zooming(float Output)
{
	Camera->FieldOfView = Output;
}
