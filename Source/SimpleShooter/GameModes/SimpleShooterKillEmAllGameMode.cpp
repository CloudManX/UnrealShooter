// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterKillEmAllGameMode.h"
	
void ASimpleShooterKillEmAllGameMode::PawnKilled(APawn* KilledPawn)
{
	Super::PawnKilled(KilledPawn);
	UE_LOG(LogTemp, Warning, TEXT("A pawn was killed"));

	APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
	if (PlayerController != nullptr)
	{	
		PlayerController->GameHasEnded(nullptr, false);
	}
}

