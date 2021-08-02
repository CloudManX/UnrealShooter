// Fill out your copyright notice in the Description page of Project Settings.

#include <TimerManager.h>
#include <Blueprint/UserWidget.h>
#include "PlayerShooterController.h"

void APlayerShooterController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	if (HUDWidget != nullptr)
	{
		HUDWidget->RemoveFromViewport();
	}


	if (bIsWinner)
	{
		DisplayWinScreen();
	}
	else
	{
		DisplayLoseScreen();
	}
	
}

void APlayerShooterController::BeginPlay()
{
	HUDWidget = CreateWidget(this, HUDClass, "HUD");
	if (HUDWidget != nullptr)
	{
		HUDWidget->AddToViewport();
	}
}

void APlayerShooterController::DisplayWinScreen()
{
	UUserWidget* WinScreen = CreateWidget(this, WinScreenClass, "WinScreen");
	if (WinScreen != nullptr)
	{
		WinScreen->AddToViewport();
	}
	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerShooterController::RestartLevel, RestartDelay);
}

void APlayerShooterController::DisplayLoseScreen()
{
	UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass, "LoseScreen");
	if (LoseScreen != nullptr)
	{
		LoseScreen->AddToViewport();
	}
	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerShooterController::RestartLevel, RestartDelay);
}
