// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AShooterCharacterController::BeginPlay()
{
    Super::BeginPlay();
    GameplayHUD = CreateWidget(this, GameplayHUDClass);
    if(GameplayHUD != nullptr)
    {
        GameplayHUD->AddToViewport();
    }
}

void AShooterCharacterController::GameHasEnded(AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    PlayerControllerRef->SetShowMouseCursor(true);
    
    GameplayHUD->RemoveFromParent();

    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }
    GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);


}
