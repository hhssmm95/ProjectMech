// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PMGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
void UPMGameInstance::Init()
{
    Super::Init();
    LoadGameAssets();
}

void UPMGameInstance::LoadGameAssets()
{
   // DataTable Load
   WeaponDataTable = LoadObject<UDataTable>(nullptr, GameConstants::WeaponDataTablePath);
   if (!WeaponDataTable)
   {
       UE_LOG(LogTemp, Error, TEXT("Failed to load DataTable: %s"), GameConstants::WeaponDataTablePath);
   }

   LoadingScreenClass = LoadClass<UUserWidget>(nullptr, GameConstants::LoadingScreenWidgetPath);
   if (!LoadingScreenClass)
   {
	   UE_LOG(LogTemp, Error, TEXT("Failed to load LoadingScreenClass: %s"), GameConstants::LoadingScreenWidgetPath);
   }

   /*
   
	HUDWidget = CreateWidget<UPMMainHUD>(GetWorld(), HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
		HUDWidget->SetFCSScreenVisiblity(true);
		UE_LOG(LogTemp, Log, TEXT("HUD Attached"));
	}
*/
}

UDataTable* UPMGameInstance::GetWeaponDataTable()
{
    return WeaponDataTable;
}


void UPMGameInstance::ActivateLoadingScreen()
{
	if (LoadingScreenWidget == nullptr)
	{
		LoadingScreenWidget = CreateWidget<UUserWidget>(this, LoadingScreenClass);
		LoadingScreenWidget->AddToRoot();

	}

	if (LoadingScreenWidget)
	{
		LoadingScreenWidget->AddToViewport();
	}

}

void UPMGameInstance::DisableLoadingScreen()
{
	if (LoadingScreenWidget)
	{
		LoadingScreenWidget->RemoveFromViewport();
		LoadingScreenWidget->RemoveFromRoot();
		LoadingScreenWidget = nullptr;
	}

}

void UPMGameInstance::TransitLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("DesertLevel"));
}
