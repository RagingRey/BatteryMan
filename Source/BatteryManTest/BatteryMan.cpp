// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan.h"

#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABatteryMan::ABatteryMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->GetCapsuleComponent()->InitCapsuleSize(45.0f, 92.0f);
	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationRoll = false;
	this->bUseControllerRotationYaw = false;

	this->GetCharacterMovement()->RotationRate = FRotator(0.0, 500.0, 0.0);
	this->GetCharacterMovement()->AirControl = 0.5f;
	this->GetCharacterMovement()->JumpZVelocity = 600.0f;
	this->GetCharacterMovement()->bOrientRotationToMovement = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(this->RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->bUsePawnControlRotation = false;

	bDead = false;
	Power = 100.0f;
}

// Called when the game starts or when spawned
void ABatteryMan::BeginPlay()
{
	Super::BeginPlay();

	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABatteryMan::OnBeginOverlap);

	if (BatteryMan_WidgetClass != nullptr)
	{
		BatteryMan_Widget = CreateWidget(GetWorld(), BatteryMan_WidgetClass);
		BatteryMan_Widget->AddToViewport();
	}
}

// Called every frame
void ABatteryMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Power -= DeltaTime * PowerThreshold;
	if(Power <= 0 && !bDead)
	{
		bDead = true;
		this->GetMesh()->SetSimulatePhysics(true);

		FTimerHandle RestartGame_TimerHandler;
		GetWorldTimerManager().SetTimer(RestartGame_TimerHandler, this, &ABatteryMan::RestartGame, 3.0f, false);
	}
}

// Called to bind functionality to input
void ABatteryMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABatteryMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABatteryMan::MoveRight);
}

void ABatteryMan::MoveForward(float Axis)
{
	if(!bDead)
	{
		const float YawRotation = this->GetControlRotation().Yaw;
		const FRotator Rotation(0, YawRotation, 0);

		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void ABatteryMan::MoveRight(float Axis)
{
	if(!bDead)
	{
		const float YawRotation = this->GetControlRotation().Yaw;
		const FRotator Rotation(0, YawRotation, 0);

		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void ABatteryMan::OnBeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if(OtherActor->ActorHasTag("Battery") && !bDead)
	{
		Power += 10.0f;
		if (Power >= 100.0f)
			Power = 100.0f;

		OtherActor->Destroy();
	}
}

void ABatteryMan::RestartGame() const
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()), false);
}