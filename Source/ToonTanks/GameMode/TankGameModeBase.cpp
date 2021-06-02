// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
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
        if(PlayerController)
        {
            PlayerController->SetPlayerEnabledState(false);
        }
    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();

        if(--TargetTurrets == 0)
            UE_LOG(LogTemp, Warning, TEXT("touche : %d"), TargetTurrets);
            HandleGameOver(true); 
    }
}

void ATankGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankGameModeBase::HandleGameStart() 
{
    TargetTurrets = GetTargetTurretCount(); 
    PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    
    GameStart();
    if(PlayerController)
    {
        PlayerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableHandle; 
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerController, &APlayerControllerBase::SetPlayerEnabledState, true);
        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false); 
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    // if(PlayerWon)
    // {
    //     GameOver(true);
    // }
    // else
    // {
    //     GameOver(false);
    // }
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount() 
{
    TArray<AActor*> TurretsActors; 
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretsActors); 
    return TurretsActors.Num(); 
}
