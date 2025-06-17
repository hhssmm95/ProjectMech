// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PMMainHUD.generated.h"

UENUM()
enum class EFCSMode : uint8
{
	Normal,
	Locked
};

/**
 * 
 */
UCLASS()
class PROJECTMECH_API UPMMainHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetFCSScreenVisiblity(bool bNewVisiblity);
	//void SetLockSightScreenVisibility(bool bNewVisiblity);
	void SetFCSMode(EFCSMode InFCSMode, FVector InTargetLocation);

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
	void SetDefeatPanelEnalble();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPMainHUDPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUserWidget> FCSScreen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCanvasPanel> _VictoryPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCanvasPanel> _DefeatPanel;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	//TObjectPtr<UUserWidget> LockSightScreen;

	UPROPERTY()
	EFCSMode CurrentFCSMode;

	/*UPROPERTY()
	FVector2D LockSightPosition;*/

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _HUDRestAPText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _HUDLSWeaponNameText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _HUDLAWeaponNameText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _HUDLSWeaponAmmoText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _HUDLAWeaponAmmoText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _HUDRSWeaponNameText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _HUDRAWeaponNameText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _HUDRSWeaponAmmoText;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UTextBlock> _HUDRAWeaponAmmoText;


};
