// Fill out your copyright notice in the Description page of Project Settings.

#include <EngineUtils.h>
#include <GameFramework/Controller.h>
#include "SimpleShooter/AIControllers/BaseCharacterAIController.h"
#include "SimpleShooterKillEmAllGameMode.h"
	
void ASimpleShooterKillEmAllGameMode::BeginPlay()
{
	Super::BeginPlay();
	for (const AController* Controller : TActorRange<AController>(GetWorld()))
	{
		const ABaseCharacterAIController* EnemyAIController = Cast<ABaseCharacterAIController>(Controller);
		if (EnemyAIController != nullptr)
		{
			EnemyCnt++;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Kill'em All mode activated! Enemy Count: %d"), EnemyCnt);
}

void ASimpleShooterKillEmAllGameMode::PawnKilled(APawn* KilledPawn)
{
	Super::PawnKilled(KilledPawn);
	UE_LOG(LogTemp, Warning, TEXT("A pawn was killed"));

	APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
	if (PlayerController != nullptr)
	{	
		EndGame(false);
	}
	else
	{
		// Potential Race Condition
		{
			FScopeLock ScopeLock(&Mutex);
			EnemyCnt--;
		}

		if (EnemyCnt == 0)
		{
			EndGame(true);
		}
	}
}

void ASimpleShooterKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
