// Fill out your copyright notice in the Description page of Project Settings.

#include <DrawDebugHelpers.h>
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>
#include "GunBase.h"

#define BULLET_TRACE_CHANNEL ECollisionChannel::ECC_GameTraceChannel1

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>("RootSceneComponent");
	SetRootComponent(RootSceneComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(RootSceneComponent);

}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunBase::PullTrigger()
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, SkeletalMeshComponent, "MuzzleFlashSocket");
		if (MuzzleSound)
		{
			UGameplayStatics::SpawnSoundAttached(MuzzleSound, SkeletalMeshComponent, "MuzzleSound");
		}
	}	

	FHitResult TraceHitResult;
	FVector InShotDirection;

	if (!GunTrace(TraceHitResult, InShotDirection)) 
	{
		return;
	}
	
	AController* OwnerController = GetOwnerController();

	FPointDamageEvent PointDamageEvent(DamageAmount, TraceHitResult, InShotDirection, DamageType);
	AActor* ActorTakesDamage = TraceHitResult.GetActor();	
	if (ActorTakesDamage)
	{
		ActorTakesDamage->TakeDamage(DamageAmount, PointDamageEvent, OwnerController, GetOwner());
	}
	
	if (ImpactEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ImpactEffect,
			TraceHitResult.Location,
			InShotDirection.Rotation()
		);

		if (ImpactSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, TraceHitResult.Location);
		}
	}

	if (IsDebugEnabled)
	{
		FVector ViewportLocation;
		FRotator ViewportRotation;
		
		OwnerController->GetPlayerViewPoint(OUT ViewportLocation, OUT ViewportRotation);	
		DrawDebugItems(ViewportLocation, ViewportRotation, TraceHitResult);
	}
}

bool AGunBase::GunTrace(FHitResult& HitResult, FVector& InShotDirection)
{
	FVector ViewportLocation;
	FRotator ViewportRotation;

	AController* OwnerController = GetOwnerController();

	OwnerController->GetPlayerViewPoint(OUT ViewportLocation, OUT ViewportRotation);	
	InShotDirection = -ViewportRotation.Vector();
	
	FVector TraceEndLocation = ViewportLocation + ViewportRotation.Vector() * MaxShootingRange;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bTraceSuccess = GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		ViewportLocation,
		TraceEndLocation,
		BULLET_TRACE_CHANNEL,
		Params);

	return bTraceSuccess;
}

AController* AGunBase::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	checkf(OwnerPawn != nullptr, TEXT("Failed to Cast the Owner of %s to APawn."), *GetName());

	AController* OwnerController = OwnerPawn->GetController();
	checkf(OwnerPawn != nullptr, TEXT("Failed to Obtain AController of %s."), *GetOwner()->GetName());

	return OwnerController;
}


void AGunBase::DrawDebugItems(const FVector& ViewportLocation, const FRotator& ViewportRotation, const FHitResult& HitResult) const
{		
	DrawDebugCamera(
		GetWorld(),
		ViewportLocation,
		ViewportRotation,
		90,
		2.f,
		FColor::Blue,
		true
	);

	DrawDebugPoint(
		GetWorld(),
		HitResult.Location,
		20.f,
		FColor::Blue,
		true
	);
}

// Called every frame
