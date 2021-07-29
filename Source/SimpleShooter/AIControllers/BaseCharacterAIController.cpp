// Fill out your copyright notice in the Description page of Project Settings.

#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>
#include "BaseCharacterAIController.h"

void ABaseCharacterAIController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Hooking Up AI Controller."));
	//SetFocus(PlayerPawn);
	if (AIBehaviorTree != nullptr)
	{
		RunBehaviorTree(AIBehaviorTree);

		GetBlackboardComponent()->SetValueAsVector("SpawnLocation", GetPawn()->GetActorLocation());
	}
}

void ABaseCharacterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//if (PlayerPawn != nullptr && LineOfSightTo(PlayerPawn))
	//{
	//	GetBlackboardComponent()->SetValueAsVector("PlayerLocation", PlayerPawn->GetActorLocation());	
	//	GetBlackboardComponent()->SetValueAsVector("LastKnownPlayerLocation", PlayerPawn->GetActorLocation());
	//}
	//else
	//{
	//	GetBlackboardComponent()->ClearValue("PlayerLocation");
	//}
}

