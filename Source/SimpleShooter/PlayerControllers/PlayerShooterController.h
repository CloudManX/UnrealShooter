// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerShooterController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API APlayerShooterController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Aiming")
	TSubclassOf<class UUserWidget> HUDClass;
	
	UPROPERTY()
	class UUserWidget* HUDWidget;

	UPROPERTY(EditAnywhere, Category = "GameEnding")
	float RestartDelay = 5.f;

	UPROPERTY(EditAnywhere, Category = "GameEnding")
	TSubclassOf<class UUserWidget> WinScreenClass;
	void DisplayWinScreen();

	UPROPERTY(EditAnywhere, Category = "GameEnding")
	TSubclassOf<class UUserWidget> LoseScreenClass;
	void DisplayLoseScreen();

	FTimerHandle RestartTimerHandle;

};
