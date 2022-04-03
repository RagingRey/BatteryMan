// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "BatteryMan.generated.h"

UCLASS()
class BATTERYMANTEST_API ABatteryMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABatteryMan();

	UPROPERTY(EditDefaultsOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
		UCameraComponent* Camera;

	bool bDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
		float Power;

	UPROPERTY(EditAnywhere, Category = Power)
		float PowerThreshold;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<UUserWidget> BatteryMan_WidgetClass;

	UUserWidget* BatteryMan_Widget;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void RestartGame() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
