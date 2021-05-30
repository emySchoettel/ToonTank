// Fill out your copyright notice in the Description page of Project Settings.

#include "PanwBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ToonTanks/Actors/ProjectileBase.h"

// Sets default values
APanwBase::APanwBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp; 

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APanwBase::RotateTurret(FVector LookAtTarget) 
{
	//Update TurretMesh rotation to face towards the LookAtTarget passed in from Child Classes 
	//TurretMesh->SetWorldRotation() ... 

	FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();
	//FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, LookAtTargetCleaned);

	TurretMesh->SetWorldRotation(TurretRotation);

}

void APanwBase::Fire() 
{
	//Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location firing towards Rotation
	if(ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* tempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation) ;
		tempProjectile->SetOwner(this); 

	}

}

void APanwBase::HandleDestruction() 
{
	// --- Universal functionality ---
	// Play death effects particle, sound and camera shake 

	// --- Then do Child overrides -- 
	// -- PawnTurret - Inform GameMode Turret died -> then destroy() self

	// -- PawnTank - Inform GameMode Player died -> then Hide() all components && stop movement input 
}

void APanwBase::BeginPlay() 
{
	Super::BeginPlay(); 
}

// Called every frame
void APanwBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APanwBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



