// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAIController.h"
#include "Components/CapsuleComponent.h"

#include "CodeNameEchoNineGameModeBase.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    FirstPoint = CreateDefaultSubobject<USceneComponent>(TEXT("First Patrol Checkpoint"));
    FirstPoint->SetupAttachment(RootComponent);

    SecondPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Second Patrol Checkpoint"));
    SecondPoint->SetupAttachment(RootComponent);

	CurHealth = MaxHealth;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Hide gun which is part of skeleton
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	AShooterAIController* EnemyController = GetController<AShooterAIController>();

	if(ensure(EnemyController != nullptr))
	{
		EnemyController->SetCheckpoints(FirstPoint->GetComponentLocation(), SecondPoint->GetComponentLocation());
	}



}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	damageApplied = FMath::Min(CurHealth, damageApplied);
	CurHealth -= damageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Current Health ENEMY %f"), CurHealth);
	if(CurHealth <= 0)
	{
		IsDead = true;
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		ACodeNameEchoNineGameModeBase* gameMode = GetWorld()->GetAuthGameMode<ACodeNameEchoNineGameModeBase>();
		if(gameMode != nullptr)
		{
			gameMode->PawnKilled(this);
		}
	}
	return damageApplied;

}


bool AEnemyCharacter::GetIsDead() const
{
	return IsDead;
}

void AEnemyCharacter::Fire()
{
	Gun->PullTrigger();
}
