// Fill out your copyright notice in the Description page of Project Settings.


#include "KillAllEnemiesGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
void AKillAllEnemiesGameMode::PawnKilled(APawn* KilledPawn)
{
    Super::PawnKilled(KilledPawn);

    //UE_LOG(LogTemp, Display, TEXT("Pawn was killed."));

    APlayerController* playerController = Cast<APlayerController>(KilledPawn->GetController());
    if(playerController != nullptr)
    {
        EndGame(false);
        return;
    }
    for(AShooterAIController* controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!controller->IsDead())
        {
            return;
        }
    }
    EndGame(true);
}

void AKillAllEnemiesGameMode::EndGame(bool bIsPlayerWinner)
{
    for(AController* controller : TActorRange<AController>(GetWorld()))
    {
        //UE_LOG(LogTemp, Display, TEXT("%s"), *controller->GetPawn()->GetName());
        bool bIsWinner =  controller->IsPlayerController() == bIsPlayerWinner;
        controller->GameHasEnded(controller->GetPawn(), bIsWinner);
       
    }
}
