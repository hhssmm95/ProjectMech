// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PMGameModeBase.h"
#include "Character/PMMechBase.h"

APMGameModeBase::APMGameModeBase()
{
	bUseSeamlessTravel = true;
}

void APMGameModeBase::DecreaseEnemyCount()
{
	RestEnemyCount -= 1;

	if (RestEnemyCount <= 0)
	{
		APMMechBase* PlayerMech = Cast<APMMechBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
		PlayerMech->HandleVictory();
	}
}
