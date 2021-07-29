// Fill out your copyright notice in the Description page of Project Settings.

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>
#include "BTService_PlayerLocationIfSeen.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	TickNode(OwnerComp, NodeMemory, DeltaSeconds);	

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;
	}
	AAIController* OwnerAIController = OwnerComp.GetAIOwner();
	if (OwnerAIController == nullptr)
	{
		return;
	}

	if (OwnerAIController->LineOfSightTo(PlayerPawn))
	{ 
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}	
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
