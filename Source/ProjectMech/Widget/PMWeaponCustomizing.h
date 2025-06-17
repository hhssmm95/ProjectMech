// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameConstants.h"
#include "PMWeaponCustomizing.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMECH_API UPMWeaponCustomizing : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	void UpdateScreenData(const FPMWeaponData& InWeaponData, EMechCustomizePart PartType);
	//FPMWeaponData GetSpecificWeaponData(EMechCustomizePart PartType, int32 Index);
	FPMWeaponData GetCurrentWeaponData();
	void SetEquippedSignVisiblity(bool bIsVisible);

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION()
	void OnRollOutButtonClicked();

	bool CheckCustomizeComplete();

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _PartCategoryText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _WeaponNameText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _DamageValueText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _ReloadTimeValueText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _MagazineSizeValueText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _ExlposionRangeValueText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UImage> _WeaponMeshImage;

	/*UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UImage> _MechMeshImage;*/

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UButton> _RollOutButton;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UBorder> _EquippedSignBorder;

protected:
	UPROPERTY()
	TObjectPtr<class APMCustomizeDummy> Mannequin;

protected:
	FPMMechData CustomizeData;
	
	TArray<FPMWeaponData> PrimaryWeaponDataArray;
	TArray<FPMWeaponData> ShoulderWeaponDataArray;
	//FPMWeaponData CurrentWeaponData;
	TArray<EMechCustomizePart> CustomizePartArray = { EMechCustomizePart::LeftPrimaryWeapon, EMechCustomizePart::RightPrimaryWeapon, 
		EMechCustomizePart::LeftShoulderWeapon, EMechCustomizePart::RightShoulderWeapon };
	int32 CurrentPartIndex = 0;
	int32 CurrentIndex = 0;
	EMechCustomizePart CurrentPartType = EMechCustomizePart::None;

	int32 LeftArmSelectedIndex = 0;
	int32 RightArmSelectedIndex = 0;
	int32 LeftShoulderSelectedIndex = 0;
	int32 RightShoulderSelectedIndex = 0;

};
