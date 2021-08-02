// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	inline void SetDebugStatus(bool IsEnable) { IsDebugEnabled = IsEnable; };
	inline bool GetDebugStatus() const { return IsDebugEnabled; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;

	// Gun Mechanics
	bool GunTrace(FHitResult& HitResult, FVector& InShotDirection);

	AController* GetOwnerController() const;

	// Particle Effects
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageAmount = 10.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float MaxShootingRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;
	
	// Debug 
	void DrawDebugItems(
		const FVector& ViewportLocation, 
		const FRotator& ViewportRotation,
		const FHitResult& HitResult) const;

	bool IsDebugEnabled = false;
};
