// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PanwBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APanwBase
{
	GENERATED_BODY()

	private : 

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm; 
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera; 

		FVector MoveDirection; 
		FQuat RotationDirection; 

		float MoveSpeed = 100.0f; 
		float RotateSpeed = 100.0f;
		
		void CalculateMoveInput(float Value);
		void CalculateRotateInput(float Value); 

		void Move();
		void Rotate(); 

	public : 

		APawnTank();

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEMO")
		// int VisibleAnywhere;
		// UPROPERTY(VisibleDefaultsOnly, Category = "DEMO")
		// int VisibleDefaultsOnly; 
		// UPROPERTY(VisibleInstanceOnly, Category = "DEMO")
		// int VisibleInstanceOnly;
		// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DEMO")
		// int EditAnywhere; 
		// UPROPERTY(EditDefaultsOnly, Category = "DEMO")
		// int EditDefaultsOnly;
		// UPROPERTY(EditInstanceOnly, Category ="DEMO")
		// int EditInstanceOnly; 

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	
};
