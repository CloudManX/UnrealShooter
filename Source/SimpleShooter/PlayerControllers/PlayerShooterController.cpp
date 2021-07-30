// Fill out your copyright notice in the Description page of Project Settings.

#include <TimerManager.h>
#include <Blueprint/UserWidget.h>
#include "PlayerShooterController.h"

void APlayerShooterController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass, "LoseScreen");
	if (LoseScreen != nullptr)
	{
		LoseScreen->AddToViewport();
	}
	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerShooterController::RestartLevel, RestartDelay);
}
