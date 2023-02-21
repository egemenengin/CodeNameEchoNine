// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodeNameEchoNineGameModeBase.h"
#include "KillAllEnemiesGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CODENAMEECHONINE_API AKillAllEnemiesGameMode : public ACodeNameEchoNineGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PawnKilled(APawn* KilledPawn) override;	

private:
	void EndGame(bool bIsPlayerWinner);	
};
