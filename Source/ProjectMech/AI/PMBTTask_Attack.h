// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PMBTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMECH_API UPMBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UPMBTTask_Attack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
