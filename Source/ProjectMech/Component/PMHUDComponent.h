// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PMHUDComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHUDInitialized);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMECH_API UPMHUDComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void InitializeHUD();

public:
	void SetFCSModeNormal(FVector InTargetLocation);
	void SetFCSModeLocked(FVector InTargetLocation);
	void SetRestAPText(FText InText);
	void SetLAWeaponNameText(FText InText);
	void SetLSWeaponNameText(FText InText);
	void SetLAWeaponAmmoText(FText InText);
	void SetLSWeaponAmmoText(FText InText);
	void SetRAWeaponNameText(FText InText);
	void SetRSWeaponNameText(FText InText);
	void SetRAWeaponAmmoText(FText InText);
	void SetRSWeaponAmmoText(FText InText);
	void SetVictoryPanelEnable();
	void SetDefeatPanelEnable();

	//delegate
public:
	UPMHUDComponent();

	FOnHUDInitialized OnHUDInitialized;

public:
	void UpdateLockSightPosition(const FVector& TargetLocation);

protected:
	UPROPERTY()
	TSubclassOf<class UPMMainHUD> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<class UPMMainHUD> HUDWidget;

	UPROPERTY()
	TSubclassOf<class UWidgetComponent> LockSightClass;

	UPROPERTY()
	TObjectPtr<class UWidgetComponent> LockSight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool bIsAI;
		
};
