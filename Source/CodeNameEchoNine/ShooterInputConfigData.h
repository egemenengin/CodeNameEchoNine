// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "ShooterInputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class CODENAMEECHONINE_API UShooterInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* InputFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* InputJump;	
};