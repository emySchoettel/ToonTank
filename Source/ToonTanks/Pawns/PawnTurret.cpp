// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    	
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(!PlayerTank || ReturnDistanceToPlayer() < FireRange)
    {
        return; 
    }

    RotateTurret(PlayerTank->GetActorLocation());
}

void APawnTurret::CheckFireCondition() 
{
    //if player == null || is dead then bail !
    if(!PlayerTank)
    {
        return; 
    }
    //if player is in range then fire !
    if(ReturnDistanceToPlayer() <= FireRange)
    {
        // Fire
        Fire(); 
        UE_LOG(LogTemp, Warning, TEXT("Fire Condition Success"));
    }
    
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if(!PlayerTank)
    {
        return 0.0f; 
    }

    return FVector::Dist(PlayerTank->GetActorLocation(), GetActorLocation());
}
