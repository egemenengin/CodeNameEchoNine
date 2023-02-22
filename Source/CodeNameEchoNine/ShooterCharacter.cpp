// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Kismet/GameplayStatics.h"

#include "ShooterInputConfigData.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"

#include "CodeNameEchoNineGameModeBase.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurHealth = MaxHealth;

	PlayerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Player Spring Arm"));
	PlayerSpringArm->SetupAttachment(RootComponent);

	PlayerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCam->SetupAttachment(PlayerSpringArm);
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Hide gun which is part of skeleton
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* playerController = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	subsystem->ClearAllMappings();
	subsystem->AddMappingContext(InputMapping, 0);
	
	//GetEnhancedInputComponent
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &AShooterCharacter::Move);
	enhancedInputComponent->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AShooterCharacter::Look);
	enhancedInputComponent->BindAction(InputActions->InputFire, ETriggerEvent::Started, this, &AShooterCharacter::Fire);
	enhancedInputComponent->BindAction(InputActions->InputJump, ETriggerEvent::Started, this, &AShooterCharacter::JumpHandle);

}


//Handle move input
void AShooterCharacter::Move(const FInputActionValue& Value)
{	
	if(Controller != nullptr)
	{

		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

		if(MoveValue.Y != 0.f)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(Direction, MoveValue.Y * GetWorld()->GetDeltaSeconds() * MovementSpeed);
		}
		if(MoveValue.X != 0.f)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
			AddMovementInput(Direction, MoveValue.X * GetWorld()->GetDeltaSeconds() * MovementSpeed);
		}


	}
}
//Handle look input
void AShooterCharacter::Look(const FInputActionValue& Value)
{
	if(Controller != nullptr)
	{
		FVector2D LookValue = Value.Get<FVector2D>();

		if(LookValue.X != 0.f)
		{
			AddControllerYawInput(LookValue.X * GetWorld()->GetDeltaSeconds() * RotationSpeed);
		}

		if(LookValue.Y != 0.f)
		{
			AddControllerPitchInput(LookValue.Y * GetWorld()->GetDeltaSeconds() * RotationSpeed);
		}
	}
}
void AShooterCharacter::JumpHandle(const FInputActionValue& Value)
{
	if(Value.Get<float>() > 0)
	{
		Jump();
	}

}
//Handle fire input
void AShooterCharacter::Fire(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("FIRE"));
	Gun->PullTrigger();

}
float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	damageApplied = FMath::Min(CurHealth, damageApplied);
	CurHealth -= damageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Current Health %f"), CurHealth);
	if(CurHealth <= 0)
	{
		IsDead = true;

		ACodeNameEchoNineGameModeBase* gameMode = GetWorld()->GetAuthGameMode<ACodeNameEchoNineGameModeBase>();
		if(gameMode != nullptr)
		{
			gameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
	return damageApplied;

}


bool AShooterCharacter::GetIsDead() const
{
	return IsDead;
}

float AShooterCharacter::GetHealthPercent() const
{
    return CurHealth/MaxHealth;
}
