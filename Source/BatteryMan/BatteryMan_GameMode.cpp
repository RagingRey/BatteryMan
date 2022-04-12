// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameMode.h"

#include "Blueprint/UserWidget.h"

ABatteryMan_GameMode::ABatteryMan_GameMode()
{

}

void ABatteryMan_GameMode::BeginPlay()
{
	Super::BeginPlay();

	InitiateWidget();
	SpawnBatteryHandle();
}

void ABatteryMan_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABatteryMan_GameMode::InitiateWidget()
{
	if (BatteryMan_Widget_Class != nullptr)
	{
		BatteryMan_Widget = CreateWidget(GetWorld(), BatteryMan_Widget_Class);
		BatteryMan_Widget->AddToViewport();
	}
}

void ABatteryMan_GameMode::SpawnBattery()
{
	if (Battery_Class != nullptr)
	{
		const float Spawn_X = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
		const float Spawn_Y = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

		const FVector SpawnLocation = FVector(Spawn_X, Spawn_Y, Spawn_Z);
		const FRotator SpawnRotation = FRotator::ZeroRotator;

		GetWorld()->SpawnActor(Battery_Class, &SpawnLocation, &SpawnRotation);
	}
}

void ABatteryMan_GameMode::SpawnBatteryHandle()
{
	FTimerHandle SpawnBattery_TimerHandle;
	GetWorldTimerManager().SetTimer(SpawnBattery_TimerHandle, this, &ABatteryMan_GameMode::SpawnBattery, 2.0f, true);
}