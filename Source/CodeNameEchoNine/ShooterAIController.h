// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class CODENAMEECHONINE_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;

	AShooterAIController();

	void SetCheckpoints(FVector firstPoint, FVector secondPoint);

	bool IsDead() const;
protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Control", meta =(AllowPrivateAccess = "true"))
	float FollowDistance = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Control", meta =(AllowPrivateAccess = "true"))
	class UBehaviorTree* AIBehavior;

	FName FirstCheckpointName = TEXT("FirstCheckpoint");
	FName SecondCheckpointName = TEXT("SecondCheckpoint");
	FVector FirstCheckpoint;
	FVector SecondCheckpoint;

	bool CheckpointsSaved = false;

};
