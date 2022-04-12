// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BatteryMan_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYMAN_API ABatteryMan_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABatteryMan_GameMode();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUserWidget> BatteryMan_Widget_Class;
	TObjectPtr<UUserWidget> BatteryMan_Widget;

	UPROPERTY(EditDefaultsOnly, Category = Battery)
		TSubclassOf<AActor> Battery_Class;

	UPROPERTY(EditDefaultsOnly, Category = SpawnParams)
		float Spawn_X_Min;

	UPROPERTY(EditDefaultsOnly, Category = SpawnParams)
		float Spawn_X_Max;

	UPROPERTY(EditDefaultsOnly, Category = SpawnParams)
		float Spawn_Y_Min;

	UPROPERTY(EditDefaultsOnly, Category = SpawnParams)
		float Spawn_Y_Max;

	const float Spawn_Z = 500.0f;

	void InitiateWidget();
	void SpawnBattery();
	void SpawnBatteryHandle();
public:
	virtual void Tick(float DeltaSeconds) override;
};
