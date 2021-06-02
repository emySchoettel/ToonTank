// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PanwBase.generated.h"

class UCapsuleComponent; 
class AProjectileBase;
class UHealthComponent; 

UCLASS()
class TOONTANKS_API APanwBase : public APawn
{
	GENERATED_BODY()

private :

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	//VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* DeathParticle; 

	UPROPERTY(EditAnywhere, Category = "Health")
	UHealthComponent* HealthComponent; 

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category ="Effects")
	TSubclassOf<UCameraShake> DeathShake; 


public:
	// Sets default values for this pawn's properties
	APanwBase();

	void PawnDestroyed(); 
	virtual void HandleDestruction(); 

	virtual void Tick(float DeltaTime) override; 

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; 

protected :

	void RotateTurret(FVector LookAtTarget);

	void Fire(); 

	virtual void BeginPlay() override;


};
