#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMagicBall.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMagicBallBeginOverlapSignature, FHitResult, InHitResult);

UCLASS()
class U07_THIRDPERSONCPP_API ACMagicBall : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMagicBall();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;
	
	// Sphere에 붙어서 따라다닐 Particle
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

private:
	// Damage를 입혔을 때 나올 Particle
	UPROPERTY(EditDefaultsOnly, Category = "Impact")
		class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Impact")
		FTransform ImpactTransform;

public:
	UPROPERTY(BlueprintAssignable)
		FMagicBallBeginOverlapSignature OnBeginOverlap;
};