// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
// #include "DrawDebugHelpers.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(Root);


}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
//MuzzleFlashSocket
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr) return;

	FVector viewportLocation;
	FRotator viewportRotation;

	OwnerController->GetPlayerViewPoint(viewportLocation, viewportRotation);
	//DrawDebugCamera(GetWorld(), viewportLocation, viewportRotation, 90, 2, FColor::Red, true);

	FVector End = viewportLocation + (viewportRotation.Vector() * Range);
	//DrawDebugPoint(GetWorld(), viewportLocation, 20, FColor::Blue, true);

	FHitResult HitResult;
	bool isHit = GetWorld()->LineTraceSingleByChannel(HitResult, viewportLocation, End, ECollisionChannel::ECC_GameTraceChannel1);

	if(isHit)
	{
		//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
		FVector ShotDirection = -viewportRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, HitResult.Location, ShotDirection.Rotation());

		AActor* HitActor = HitResult.GetActor();
		if(HitActor != nullptr)
		{
			FPointDamageEvent WeaponDamageEvent(Damage, HitResult, ShotDirection, nullptr);

			HitActor->TakeDamage(Damage, WeaponDamageEvent, OwnerController, this);
		}
	}
}