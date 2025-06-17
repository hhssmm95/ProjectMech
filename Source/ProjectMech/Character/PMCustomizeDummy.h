// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameConstants.h"
#include "GameFramework/Character.h"
#include "PMCustomizeDummy.generated.h"

UCLASS()
class PROJECTMECH_API APMCustomizeDummy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APMCustomizeDummy();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(EMechCustomizePart PartName, const FPMWeaponData& InWeaponData);

	virtual void BeginPlay() override;

protected:
	//slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> RightArmWeaponSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> LeftArmWeaponSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> RightShoulderWeaponSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> LeftShoulderWeaponSlot;

	//weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class APMMechWeapon> RightArmWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class APMMechWeapon> LeftArmWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class APMMechWeapon> RightShoulderWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class APMMechWeapon> LeftShoulderWeapon;

};
