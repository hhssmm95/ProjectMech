// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PMHUDComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/PMMainHUD.h"
#include "Blueprint/UserWidget.h"



UPMHUDComponent::UPMHUDComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;
	ConstructorHelpers::FClassFinder<UPMMainHUD> HUDClassRef(TEXT("/Game/ProjectMech/Blueprint/Widget/WBP_MainHUD.WBP_MainHUD_C"));
	if (HUDClassRef.Class)
	{
		HUDWidgetClass = HUDClassRef.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> LockSightClassRef(TEXT("/Game/ProjectMech/Blueprint/Widget/WBP_LockOnScreen.WBP_LockOnScreen_C"));
	if (LockSightClassRef.Class)
	{
		LockSight = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockSightWidget"));
		LockSight->SetWidgetClass(LockSightClassRef.Class);
		LockSight->SetWidgetSpace(EWidgetSpace::Screen); // 스크린 공간에서 UI 표시
		LockSight->SetDrawSize(FVector2D(320, 320)); // 위젯 크기 설정
	}
	

}

void UPMHUDComponent::UpdateLockSightPosition(const FVector& TargetLocation)
{
	/*APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController || !LockSight) return;*/

	//FVector2D ScreenPosition;
	//bool bIsOnScreen = PlayerController->ProjectWorldLocationToScreen(TargetLocation, ScreenPosition);

	//if (bIsOnScreen)
	//{
	//	LockSight->SetRenderTranslation(ScreenPosition); // UI 위치 업데이트
	//}

	LockSight->SetWorldLocation(TargetLocation);
}


void UPMHUDComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!bIsAI)
	{
		InitializeHUD();
	}
	LockSight->SetVisibility(false);
}

void UPMHUDComponent::InitializeHUD()
{

	HUDWidget = CreateWidget<UPMMainHUD>(GetWorld(), HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
		HUDWidget->SetFCSScreenVisiblity(true);
		UE_LOG(LogTemp, Log, TEXT("HUD Attached"));
	}

	if (LockSight)
	{
		LockSight->RegisterComponent();
		LockSight->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}


	OnHUDInitialized.Broadcast();
}

void UPMHUDComponent::SetFCSModeNormal(FVector InTargetLocation)
{
	LockSight->SetVisibility(false);
	HUDWidget->SetFCSMode(EFCSMode::Normal, InTargetLocation);
}

void UPMHUDComponent::SetFCSModeLocked(FVector InTargetLocation)
{
	LockSight->SetVisibility(true);
	UpdateLockSightPosition(InTargetLocation);
	HUDWidget->SetFCSMode(EFCSMode::Locked, InTargetLocation);
}
void UPMHUDComponent::SetRestAPText(FText InText)
{
	HUDWidget->SetRestAPText(InText);
}
void UPMHUDComponent::SetLAWeaponNameText(FText InText)
{
	HUDWidget->SetLAWeaponNameText(InText);
}
void UPMHUDComponent::SetLSWeaponNameText(FText InText)
{
	HUDWidget->SetLSWeaponNameText(InText);
}
void UPMHUDComponent::SetLAWeaponAmmoText(FText InText)
{
	HUDWidget->SetLAWeaponAmmoText(InText);
}
void UPMHUDComponent::SetLSWeaponAmmoText(FText InText)
{
	HUDWidget->SetLSWeaponAmmoText(InText);
}
void UPMHUDComponent::SetRAWeaponNameText(FText InText)
{
	HUDWidget->SetRAWeaponNameText(InText);
}
void UPMHUDComponent::SetRSWeaponNameText(FText InText)
{
	HUDWidget->SetRSWeaponNameText(InText);
}
void UPMHUDComponent::SetRAWeaponAmmoText(FText InText)
{
	HUDWidget->SetRAWeaponAmmoText(InText);
}
void UPMHUDComponent::SetRSWeaponAmmoText(FText InText)
{
	HUDWidget->SetRSWeaponAmmoText(InText);
}
void UPMHUDComponent::SetVictoryPanelEnable()
{
	HUDWidget->SetVictoryPanelEnable();
}
void UPMHUDComponent::SetDefeatPanelEnable()
{
	HUDWidget->SetDefeatPanelEnalble();
}
//
//void UPMHUDComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}
//
