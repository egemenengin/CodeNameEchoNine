// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class CODENAMEECHONINE_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnyWhere, Category = "Effects")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnyWhere, Category = "Effects")
	UParticleSystem* HitFlash;

	UPROPERTY(EditAnyWhere)
	float Range = 5000;

	UPROPERTY(EditAnywhere)
	float Damage = 25;
};
