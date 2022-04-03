// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameMode.h"

#include "Blueprint/UserWidget.h"

ABatteryMan_GameMode::ABatteryMan_GameMode()
{
	
}

void ABatteryMan_GameMode::BeginPlay()
{
	Super::BeginPlay();

	float SpawnRate = FMath::RandRange(1, 3);
	FTimerHandle SpawnBatteries_TimerHandler;

	GetWorldTimerManager().SetTimer(SpawnBatteries_TimerHandler, this, &ABatteryMan_GameMode::SpawnBatteries, SpawnRate, true);
}

void ABatteryMan_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABatteryMan_GameMode::SpawnBatteries() const
{
	const float Spawn_X = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	const float Spawn_Y = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	const FVector SpawnLocation = FVector(Spawn_X, Spawn_Y, Spawn_Z);
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	GetWorld()->SpawnActor(Battery, &SpawnLocation, &SpawnRotation);
}
