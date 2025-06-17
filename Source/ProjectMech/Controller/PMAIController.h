// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PMAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMECH_API APMAIController : public AAIController
{
	GENERATED_BODY()
//
public:
	//APMAIController();

	void UpdateMainTarget(AActor* MainTarget);
	void UpdateTargetLocation(FVector InLocation);
	void SetAimAcceptableRadius(float InRadius);
	void SetAsSniper(bool IsSniper);
	void SetEnableBrainComponent(bool InEnable);
	void SetIsInAcceptableDist(bool IsInDist);
	virtual void OnPossess(APawn* InPawn) override;
	
protected:
	//virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr <UBlackboardData> BlackboardData;

	TObjectPtr<AActor> TargetMech;


};
