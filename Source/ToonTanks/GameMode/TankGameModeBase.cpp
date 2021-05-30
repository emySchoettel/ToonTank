// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay(); 
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    //UE_LOG(LogTemp, Warning, TEXT("A pawn died"));
    if(DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction(); 
        HandleGameOver(false); 
    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();

        if(--TargetTurrets == 0)
            HandleGameOver(false); 
    }
}

void ATankGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankGameModeBase::HandleGameStart() 
{
    TargetTurrets = GetTargetTurretCount(); 

    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    
    GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount() 
{
    TArray<AActor*> TurretsActors; 
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretsActors); 
    return TurretsActors.Num(); 
}
