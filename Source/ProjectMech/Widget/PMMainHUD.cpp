// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PMMainHUD.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"

void UPMMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	_HUDRestAPText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("HUD_RestAPText")));
	if (!_HUDRestAPText)
	{
		UE_LOG(LogTemp, Error, TEXT("HUDRestAPText is not Initialized"));
	}

	//left
	_HUDLSWeaponNameText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("HUD_LSWeaponNameText")));
	if (!_HUDLSWeaponNameText)
	{
		UE_LOG(LogTemp, Error, TEXT("_HUDLSWeaponNameText is not Initialized"));
	}

	_HUDLAWeaponNameText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("HUD_LAWeaponNameText")));
	if (!_HUDLAWeaponNameText)
	{
		UE_LOG(LogTemp, Error, TEXT("_HUDLAWeaponNameText is not Initialized"));
	}

	_HUDLSWeaponAmmoText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("HUD_LSWeaponAmmoText")));
	if (!_HUDLSWeaponAmmoText)
	{
		UE_LOG(LogTemp, Error, TEXT("_HUDLSWeaponAmmoText is not Initialized"));
	}

	_HUDLAWeaponAmmoText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("HUD_LAWeaponAmmoText")));
	if (!_HUDLAWeaponAmmoText)
	{
		UE_LOG(LogTemp, Error, TEXT("_HUDLAWeaponAmmoText is not Initialized"));
	}

	//right
	_HUDRSWeaponNameText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("HUD_RSWeaponNameText")));
	if (!_HUDRSWeaponNameText)
	{
		UE_LOG(LogTemp, Error, TEXT("_HUDRSWeaponNameText is not Initialized"));
	}

	_HUDRAWeaponNameText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("HUD_RAWeaponNameText")));
	if (!_HUDRAWeaponNameText)
	{
		UE_LOG(LogTemp, Error, TEXT("_HUDRAWeaponNameText is not Initialized"));
	}

	_HUDRSWeaponAmmoText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("HUD_RSWeaponAmmoText")));
	if (!_HUDRSWeaponAmmoText)
	{
		UE_LOG(LogTemp, Error, TEXT("_HUDRSWeaponAmmoText is not Initialized"));
	}

	_HUDRAWeaponAmmoText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("HUD_RAWeaponAmmoText")));
	if (!_HUDRAWeaponAmmoText)
	{
		UE_LOG(LogTemp, Error, TEXT("_HUDRAWeaponAmmoText is not Initialized"));
	}

	_VictoryPanel = Cast<UCanvasPanel>(WidgetTree->FindWidget(FName("VictoryPanel")));
	if (!_VictoryPanel)
	{
		UE_LOG(LogTemp, Error, TEXT("_VictoryPanel is not Initialized"));
	}

	_DefeatPanel = Cast<UCanvasPanel>(WidgetTree->FindWidget(FName("DefeatPanel")));
	if (!_DefeatPanel)
	{
		UE_LOG(LogTemp, Error, TEXT("_DefeatPanel is not Initialized"));
	}
}

void UPMMainHUD::SetFCSScreenVisiblity(bool bNewVisiblity)
{
	if (bNewVisiblity)
	{
		FCSScreen->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		FCSScreen->SetVisibility(ESlateVisibility::Collapsed);
	}
}

//void UPMMainHUD::SetLockSightScreenVisibility(bool bNewVisiblity)
//{
//	if (bNewVisiblity)
//	{
//		LockSightScreen->SetVisibility(ESlateVisibility::HitTestInvisible);
//	}
//	else
//	{
//		LockSightScreen->SetVisibility(ESlateVisibility::Collapsed);
//	}
//}

void UPMMainHUD::SetFCSMode(EFCSMode InFCSMode, const FVector InTargetLocation)
{
	//UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(LockSightScreen->Slot);
	switch (InFCSMode)
	{
	case EFCSMode::Normal:
		SetFCSScreenVisiblity(true);
		//SetLockSightScreenVisibility(false);
		break;

	case EFCSMode::Locked:
		/*GetOwningPlayer()->ProjectWorldLocationToScreen(InTargetLocation, LockSightPosition);
		UE_LOG(LogTemp, Log, TEXT("Lock On Target Position : %s"), *InTargetLocation.ToString());*/
		SetFCSScreenVisiblity(false);
		/*SetLockSightScreenVisibility(true);*/

		//LockSightScreen->SetPositionInViewport(LockSightPosition, false);
		//LockSightScreen->SetRenderTranslation(LockSightPosition);
		//if (CanvasSlot)
		//{
		//	CanvasSlot->SetPosition(LockSightPosition); // 목표 위치 적용
		//}
		break;

	default:
		break;
	}
}

void UPMMainHUD::SetRestAPText(FText InText)
{
	_HUDRestAPText->SetText(InText);
}

void UPMMainHUD::SetLAWeaponNameText(FText InText)
{
	_HUDLAWeaponNameText->SetText(InText);
}

void UPMMainHUD::SetLSWeaponNameText(FText InText)
{
	_HUDLSWeaponNameText->SetText(InText);
}

void UPMMainHUD::SetLAWeaponAmmoText(FText InText)
{
	_HUDLAWeaponAmmoText->SetText(InText);
}

void UPMMainHUD::SetLSWeaponAmmoText(FText InText)
{
	_HUDLSWeaponAmmoText->SetText(InText);
}

void UPMMainHUD::SetRAWeaponNameText(FText InText)
{
	_HUDRAWeaponNameText->SetText(InText);
}

void UPMMainHUD::SetRSWeaponNameText(FText InText)
{
	_HUDRSWeaponNameText->SetText(InText);
}

void UPMMainHUD::SetRAWeaponAmmoText(FText InText)
{
	_HUDRAWeaponAmmoText->SetText(InText);
}

void UPMMainHUD::SetRSWeaponAmmoText(FText InText)
{
	_HUDRSWeaponAmmoText->SetText(InText);
}


void UPMMainHUD::SetVictoryPanelEnable()
{
	_VictoryPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UPMMainHUD::SetDefeatPanelEnalble()
{
	_DefeatPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
}
