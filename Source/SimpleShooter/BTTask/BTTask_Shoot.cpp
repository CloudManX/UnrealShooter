// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "BTTask_Shoot.h"

UBTTask_Shoot::UBTTask_Shoot()
{	
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* OwnerAIController = OwnerComp.GetAIOwner();
	if (OwnerAIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	AShooterCharacter* OwnerShooterCharacter = Cast<AShooterCharacter>(OwnerAIController->GetPawn());
	if (OwnerShooterCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	OwnerShooterCharacter->Shoot();

	return EBTNodeResult::Succeeded;
}
