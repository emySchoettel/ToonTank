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

void APawnTurret::HandleDestruction() 
{
    //Call base pawn class HandleDestruction to play effects 
    Super::HandleDestruction();
    Destroy();
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
    if(!PlayerTank || !PlayerTank->GetIsPlayerAlive())
    {
        return; 
    }
    //if player is in range then fire !
    if(ReturnDistanceToPlayer() <= FireRange)
    {
        // Fire
        Fire(); 
    }    
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if(!PlayerTank)
    {
        return 0.0f; 
    }

    float dist = (PlayerTank->GetActorLocation() - GetActorLocation()).Size();
    return dist; 
    //return FVector::Dist(PlayerTank->GetActorLocation(), GetActorLocation());
}

APawnTurret::APawnTurret() 
{
    
}
