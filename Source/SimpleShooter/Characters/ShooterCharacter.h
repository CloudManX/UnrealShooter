// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGunBase;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();	

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/******************** Input Functions **********************/
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	// void LookUpRate(float AxisValue);
	// void LookRightRate(float AxisValue);

	// UPROPERTY(EditAnywhere)
	// float RotationRate = 10;

	/******************** Health **********************/
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere)
	float Health;

	/******************** Weapon **********************/
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGunBase> GunClass;

	UPROPERTY()
	AGunBase* Gun;

	/******************** Debug **********************/
	void ToggleDebugStatus();
};
