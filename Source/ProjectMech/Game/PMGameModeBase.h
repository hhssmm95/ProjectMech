// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PMGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMECH_API APMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APMGameModeBase();

	void DecreaseEnemyCount();

protected:
	int32 RestEnemyCount = 11;
};
