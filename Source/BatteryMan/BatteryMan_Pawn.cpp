// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_Pawn.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABatteryMan_Pawn::ABatteryMan_Pawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->GetCapsuleComponent()->InitCapsuleSize(45.0f, 92.0f);
	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationYaw = false;
	this->bUseControllerRotationRoll = false;

	this->GetCharacterMovement()->RotationRate = FRotator(0, 500.0f, 0);
	this->GetCharacterMovement()->AirControl = 1.0f;
	this->GetCharacterMovement()->JumpZVelocity = 600.0f;
	this->GetCharacterMovement()->bOrientRotationToMovement = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetupAttachment(this->RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->bUsePawnControlRotation = false;

	bDead = false;
	Power = 100.0f;
	Score = 0;
}

// Called when the game starts or when spawned
void ABatteryMan_Pawn::BeginPlay()
{
	Super::BeginPlay();

	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABatteryMan_Pawn::OnBeginOverlap);
}

// Called every frame
void ABatteryMan_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bDead)
	{
		Power -= DeltaTime * PowerThreshold;
	}

	if(Power <= 0)
	{
		bDead = true;
		this->GetMesh()->SetSimulatePhysics(true);

		FTimerHandle RestartGame_TimerHandler;
		GetWorldTimerManager().SetTimer(RestartGame_TimerHandler, this, &ABatteryMan_Pawn::RestartGame, 3.0f, false);
	}
}

// Called to bind functionality to input
void ABatteryMan_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ABatteryMan_Pawn::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ABatteryMan_Pawn::MoveRight);
}

void ABatteryMan_Pawn::MoveForward(float Axis)
{
	if (!bDead)
	{
		const float YawRotation = this->GetControlRotation().Yaw;
		const FRotator Rotation(0, YawRotation, 0);

		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void ABatteryMan_Pawn::MoveRight(float Axis)
{
	if (!bDead)
	{
		const float YawRotation = this->GetControlRotation().Yaw;
		const float RollRotation = this->GetControlRotation().Roll;
		const FRotator Rotation(0, YawRotation, RollRotation);

		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void ABatteryMan_Pawn::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSeep, const FHitResult& HitResult)
{
	if(OtherActor->ActorHasTag("Battery") && !bDead)
	{
		Power += 10.0f;
		if (Power > 100.0f)
			Power = 100.0f;

		Score += 10;

		OtherActor->Destroy();
	}
}

void ABatteryMan_Pawn::RestartGame() const
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()), false);
}