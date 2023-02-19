// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LastSeenPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class CODENAMEECHONINE_API UBTService_LastSeenPlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_LastSeenPlayerLocation();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;	
};
