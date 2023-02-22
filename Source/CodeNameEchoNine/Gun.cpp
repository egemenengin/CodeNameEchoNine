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
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket") );
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket") );

	FHitResult HitResult;
	FVector ShotDirection;
	if(GunTrace(HitResult, ShotDirection))
	{
		//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
		AActor* HitActor = HitResult.GetActor();
		if(HitActor != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, HitResult.Location, ShotDirection.Rotation());
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, HitResult.Location, 0.3f);

			FPointDamageEvent WeaponDamageEvent(Damage, HitResult, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();	
			HitActor->TakeDamage(Damage, WeaponDamageEvent, OwnerController, this);
		}
	}
}

bool AGun::GunTrace(FHitResult &hitResult, FVector &ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if(OwnerController == nullptr) return false;

	FVector viewportLocation;
	FRotator viewportRotation;
	OwnerController->GetPlayerViewPoint(viewportLocation, viewportRotation);
	ShotDirection = -viewportRotation.Vector();
	//DrawDebugCamera(GetWorld(), viewportLocation, viewportRotation, 90, 2, FColor::Red, true);

	FVector End = viewportLocation + (viewportRotation.Vector() * Range);

	//DrawDebugPoint(GetWorld(), viewportLocation, 20, FColor::Blue, true);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	
	return GetWorld()->LineTraceSingleByChannel(hitResult, viewportLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	
}


AController *AGun::GetOwnerController() const
{
    
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}


