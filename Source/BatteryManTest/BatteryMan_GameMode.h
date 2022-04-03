// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BatteryMan_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYMANTEST_API ABatteryMan_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABatteryMan_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Battery)
		TSubclassOf<APawn> Battery;

	const float Spawn_Z = 500.0f;

	UPROPERTY(EditAnywhere, Category = Battery)
		float Spawn_X_Min;

	UPROPERTY(EditAnywhere, Category = Battery)
		float Spawn_X_Max;

	UPROPERTY(EditAnywhere, Category = Battery)
		float Spawn_Y_Min;

	UPROPERTY(EditAnywhere, Category = Battery)
		float Spawn_Y_Max;

	void SpawnBatteries() const;
};
