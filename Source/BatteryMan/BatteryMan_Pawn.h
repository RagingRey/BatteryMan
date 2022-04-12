// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BatteryMan_GameMode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "BatteryMan_Pawn.generated.h"

UCLASS()
class BATTERYMAN_API ABatteryMan_Pawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABatteryMan_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float bDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerScore)
		int Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
		float Power;

	UPROPERTY(EditDefaultsOnly, Category = Power)
		float PowerThreshold;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
		UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = GameMode)
		TSubclassOf<ABatteryMan_GameMode> GameMode_Class;
	TObjectPtr<ABatteryMan_GameMode> GameMode;

	void MoveForward(float Axis);
	void MoveRight(float Axis);

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSeep, const FHitResult& HitResult);

	void RestartGame() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};