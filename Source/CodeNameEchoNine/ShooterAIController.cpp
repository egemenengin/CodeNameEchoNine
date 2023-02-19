// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


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
    GetBlackboardComponent()->SetValueAsVector(TEXT("FirstCheckpoint"), firstPoint);
    GetBlackboardComponent()->SetValueAsVector(TEXT("SecondCheckpoint"), secondPoint);
}