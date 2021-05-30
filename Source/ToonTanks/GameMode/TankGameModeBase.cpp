// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay(); 
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    UE_LOG(LogTemp, Warning, TEXT("A pawn died"));
}

void ATankGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void ATankGameModeBase::HandleGameStart() 
{
    
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    
}



