// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PMMechPartBase.h"
#include "../GameConstants.h"
#include "PMMechWeapon.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponFired, FText, AmmoCount);


/**
 * 
 */
UCLASS()
class PROJECTMECH_API APMMechWeapon : public APMMechPartBase
{
	GENERATED_BODY()
	
public:
	APMMechWeapon();

	void InitializeWeaponData(const FPMWeaponData& InWeaponData, FName TeamTag);
	void Shot(FVector LockedLocation);

	FORCEINLINE bool GetbIsInitialized() { return bIsInitialized; }

public:
	FOnWeaponFired OnWeaponFired;

protected:
	FPMWeaponData WeaponData;

	//FStreamableManager StreamableManager;
	UPROPERTY();
	TSubclassOf<class APMProjectile> ProjectileClass = nullptr;

	UPROPERTY();
	TSubclassOf<class APMEffectPlayer> EffectPlayerClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> WeaponMesh = nullptr;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Muzzle")
	TObjectPtr<class UParticleSystemComponent> MuzzleFlashEffect = nullptr;

	UPROPERTY()
	FTimerHandle FireRateHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 RestAmmo = 0;


	bool bIsInitialized = false;
	bool bIsReloaded = false;
};
