// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "PMBTTask_DynamicMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMECH_API UPMBTTask_DynamicMoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:
	UPMBTTask_DynamicMoveTo(); 
	
	UPROPERTY(EditAnywhere)
	float DefaultAcceptableRadius;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
