// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../GameConstants.h"
#include "PMGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMECH_API UPMGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	virtual void Init();
	void LoadGameAssets();
	
public:
	UFUNCTION()
	UDataTable* GetWeaponDataTable();

	UFUNCTION()
	void SetMechCustomizeData(const FPMMechData& InMechData) { MechCustomizeData = InMechData; }

	UFUNCTION()
	FPMMechData GetMechCustomizeData() { return MechCustomizeData; }

	UFUNCTION()
	void ActivateLoadingScreen();


	UFUNCTION()
	void DisableLoadingScreen();

	UFUNCTION()
	void TransitLevel();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable")
	TObjectPtr<UDataTable> WeaponDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MechData")
	FPMMechData MechCustomizeData;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Loading")
	TSubclassOf<UUserWidget> LoadingScreenClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Loading")
	TObjectPtr<UUserWidget> LoadingScreenWidget;
};
