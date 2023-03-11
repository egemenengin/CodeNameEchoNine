// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"

AShooterAIController::AShooterAIController()
{


}

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    if(AIBehavior != nullptr)
    {     
        RunBehaviorTree(AIBehavior);
    }
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if(!CheckpointsSaved && GetBlackboardComponent() != nullptr)
    {
        GetBlackboardComponent()->SetValueAsVector(FirstCheckpointName, FirstCheckpoint);
        GetBlackboardComponent()->SetValueAsVector(SecondCheckpointName, SecondCheckpoint);
        CheckpointsSaved = true;
    }
   /*
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(LineOfSightTo(PlayerPawn))
    {
        //SetFocus(PlayerPawn);
       //MoveToActor(PlayerPawn, FollowDistance);
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), GetBlackboardComponent()->GetValueAsVector(TEXT("PlayerLocation")));
    }
    else
    {
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
        //ClearFocus(EAIFocusPriority::Gameplay);
        //StopMovement();
    }*/
}
void AShooterAIController::SetCheckpoints(FVector firstPoint, FVector secondPoint)
{
    FirstCheckpoint = firstPoint;
    SecondCheckpoint = secondPoint;
}

bool AShooterAIController::IsDead() const
{
    AEnemyCharacter* controlledCharacter = Cast<AEnemyCharacter>(GetPawn());
    if(controlledCharacter != nullptr)
    {
        return controlledCharacter->GetIsDead();
    } 
    return true;
}
