// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PMWeaponCustomizing.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Character/PMMechBase.h"
#include "Game/PMGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PMCustomizeDummy.h"

void UPMWeaponCustomizing::NativeConstruct()
{
	_PartCategoryText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("PartCategoryText")));
	if (!_PartCategoryText)
	{
		UE_LOG(LogTemp, Error, TEXT("PartCategoryText is not Initialized"));
	}

	_WeaponNameText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("WeaponNameText")));
	if (!_WeaponNameText)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponNameText is not Initialized"));
	}

	_DamageValueText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("DamageValueText")));
	if (!_DamageValueText)
	{
		UE_LOG(LogTemp, Error, TEXT("DamageValueText is not Initialized"));
	}

	_ReloadTimeValueText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("ReloadTimeValueText")));
	if (!_ReloadTimeValueText)
	{
		UE_LOG(LogTemp, Error, TEXT("ReloadTimeValueText is not Initialized"));
	}

	_MagazineSizeValueText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("MagazineSizeValueText")));
	if (!_MagazineSizeValueText)
	{
		UE_LOG(LogTemp, Error, TEXT("MagazineSizeValueText is not Initialized"));
	}

	_ExlposionRangeValueText = Cast<UTextBlock>(WidgetTree->FindWidget(FName("ExlposionRangeValueText")));
	if (!_ExlposionRangeValueText)
	{
		UE_LOG(LogTemp, Error, TEXT("ExlposionRangeValueText is not Initialized"));
	}

	_WeaponMeshImage = Cast<UImage>(WidgetTree->FindWidget(FName("WeaponMeshImage")));
	if (!_WeaponMeshImage)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponMeshImage is not Initialized"));
	}

	/*_MechMeshImage = Cast<UImage>(WidgetTree->FindWidget(FName("MechMeshImage")));
	if (!_MechMeshImage)
	{
		UE_LOG(LogTemp, Error, TEXT("MechMeshImage is not Initialized"));
	}*/

	_RollOutButton = Cast<UButton>(WidgetTree->FindWidget(FName("RollOutButton")));
	if (!_RollOutButton)
	{
		UE_LOG(LogTemp, Error, TEXT("RollOutButton is not Initialized"));
	}
	_EquippedSignBorder = Cast<UBorder>(WidgetTree->FindWidget(FName("EquippedSignBorder")));
	if (!_EquippedSignBorder)
	{
		UE_LOG(LogTemp, Error, TEXT("EquippedSignBorder is not Initialized"));
	}

	_RollOutButton->OnClicked.AddDynamic(this, &UPMWeaponCustomizing::OnRollOutButtonClicked);
	_RollOutButton->SetIsEnabled(false);


	UPMGameInstance* GameInstance = Cast<UPMGameInstance>(GetGameInstance());
	TArray<FPMWeaponData*> AllWeaponDataRows;
	GameInstance->GetWeaponDataTable()->GetAllRows(TEXT("Gettiing All Weapon Data"), AllWeaponDataRows);

	if (!AllWeaponDataRows.IsEmpty())
	{
		for (const FPMWeaponData* WeaponDataRow : AllWeaponDataRows)
		{
			switch (WeaponDataRow->MountingPlace)
			{	
			case EMechPartType::None:
				break;
			case EMechPartType::Core:
				break;
			case EMechPartType::Thruster:
				break;
			case EMechPartType::PrimaryWeapon:
				PrimaryWeaponDataArray.Add(*WeaponDataRow);
				break;
			case EMechPartType::ShoulderWeapon:
				ShoulderWeaponDataArray.Add(*WeaponDataRow);
				break;
			case EMechPartType::FCS:
				break;
			default:
				break;
			}
		}
	}

	SetEquippedSignVisiblity(false);
	CurrentPartType = EMechCustomizePart::LeftPrimaryWeapon;
	CurrentPartIndex = 0;
	CurrentIndex = 0;

	UpdateScreenData(GetCurrentWeaponData(), CurrentPartType);

	Mannequin = Cast<APMCustomizeDummy>(GetOwningPlayerPawn());
	if (!Mannequin)
	{
		UE_LOG(LogTemp, Log, TEXT("Mannequin is not initialized yet"));
	}
}

void UPMWeaponCustomizing::UpdateScreenData(const FPMWeaponData& InWeaponData, EMechCustomizePart PartType)
{

	SetEquippedSignVisiblity(false);

	UEnum* PartTypeEnum = StaticEnum<EMechCustomizePart>();

	FText PartTypeText = PartTypeEnum->GetDisplayNameTextByValue(static_cast<int32>(PartType));
	_PartCategoryText->SetText(PartTypeText);

	_WeaponNameText->SetText(FText::FromString(InWeaponData.WeaponName));

	_DamageValueText->SetText(FText::AsNumber(InWeaponData.Damage));

	_ReloadTimeValueText->SetText(FText::AsNumber(InWeaponData.ReloadTime));

	_MagazineSizeValueText->SetText(FText::AsNumber(InWeaponData.MaxMagazine));

	_ExlposionRangeValueText->SetText(FText::AsNumber(InWeaponData.ExplosionRange));

	_WeaponMeshImage->SetBrushFromTexture(InWeaponData.Thumbnail.LoadSynchronous(), true);


	//TODO: 이미지 관련도 넣어야함 (렌더타겟)무기 및 캐릭터


	switch (PartType)
	{
	case EMechCustomizePart::None:
		break;
	case EMechCustomizePart::LeftPrimaryWeapon:
		if (CustomizeData.LeftPrimaryWeaponID == InWeaponData.ID)
		{
			SetEquippedSignVisiblity(true);
		}
		break;
	case EMechCustomizePart::RightPrimaryWeapon:
		if (CustomizeData.RightPrimaryWeaponID == InWeaponData.ID)
		{
			SetEquippedSignVisiblity(true);
		}
		break;
	case EMechCustomizePart::LeftShoulderWeapon:
		if (CustomizeData.LeftShoulderWeaponID == InWeaponData.ID)
		{
			SetEquippedSignVisiblity(true);
		}
		break;
	case EMechCustomizePart::RightShoulderWeapon:
		if (CustomizeData.RightShoulderWeaponID == InWeaponData.ID)
		{
			SetEquippedSignVisiblity(true);
		}
		break;
	default:
		break;
	}
	
}

//FPMWeaponData UPMWeaponCustomizing::GetSpecificWeaponData(EMechCustomizePart PartType, int32 Index)
//{
//	int32 FinalIndex;
//
//	switch (PartType)
//	{
//	case EMechCustomizePart::None:
//		break;
//	case EMechCustomizePart::LeftPrimaryWeapon:
//	case EMechCustomizePart::RightPrimaryWeapon:
//		if (Index >= ArmWeaponDataArray.Num())
//		{
//			FinalIndex = ArmWeaponDataArray.Num() - 1;
//		}
//		return ArmWeaponDataArray[FinalIndex];
//		break;
//
//	case EMechCustomizePart::LeftShoulderWeapon:
//	case EMechCustomizePart::RightShoulderWeapon:
//		if (Index >= ShoulderWeaponDataArray.Num())
//		{
//			FinalIndex = ShoulderWeaponDataArray.Num() - 1;
//		}
//		return ShoulderWeaponDataArray[FinalIndex];
//		break;
//	default:
//		break;
//	}
//
//
//	UE_LOG(LogTemp, Error, TEXT("Unable WeaponType Used"));
//	return FPMWeaponData();
//}

FPMWeaponData UPMWeaponCustomizing::GetCurrentWeaponData()
{
	switch (CurrentPartType)
	{
	case EMechCustomizePart::None:
		break;
	case EMechCustomizePart::LeftPrimaryWeapon:
		if (CurrentIndex >= PrimaryWeaponDataArray.Num())
		{
			CurrentIndex = PrimaryWeaponDataArray.Num() - 1;
		}
		return PrimaryWeaponDataArray[CurrentIndex];
		break;
	case EMechCustomizePart::RightPrimaryWeapon:
		if (CurrentIndex >= PrimaryWeaponDataArray.Num())
		{
			CurrentIndex = PrimaryWeaponDataArray.Num() - 1;
		}
		return PrimaryWeaponDataArray[CurrentIndex];
		break;

	case EMechCustomizePart::LeftShoulderWeapon:
		if (CurrentIndex >= ShoulderWeaponDataArray.Num())
		{
			CurrentIndex = ShoulderWeaponDataArray.Num() - 1;
		}
		return ShoulderWeaponDataArray[CurrentIndex];
		break;
	case EMechCustomizePart::RightShoulderWeapon:
		if (CurrentIndex >= ShoulderWeaponDataArray.Num())
		{
			CurrentIndex = ShoulderWeaponDataArray.Num() - 1;
		}
		return ShoulderWeaponDataArray[CurrentIndex];
		break;
	default:
		break;
	}


	UE_LOG(LogTemp, Error, TEXT("Unable WeaponType Used"));
	return FPMWeaponData();
}

void UPMWeaponCustomizing::SetEquippedSignVisiblity(bool bIsVisible)
{
	if (bIsVisible)
	{
		_EquippedSignBorder->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		_EquippedSignBorder->SetVisibility(ESlateVisibility::Hidden);
	}
}

FReply UPMWeaponCustomizing::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);


	if (InKeyEvent.GetKey() == EKeys::Enter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enter Key Pressed!"));

		const FPMWeaponData& CurrentWeaponData = GetCurrentWeaponData();

		switch (CurrentPartType)
		{
		case EMechCustomizePart::None:
			break;
		case EMechCustomizePart::LeftPrimaryWeapon:
			if (CustomizeData.LeftPrimaryWeaponID != CurrentWeaponData.ID)
			{
				CustomizeData.LeftPrimaryWeaponID = CurrentWeaponData.ID;
				Mannequin->EquipWeapon(CurrentPartType, CurrentWeaponData);
				SetEquippedSignVisiblity(true);
				CheckCustomizeComplete();
			}
			break;
		case EMechCustomizePart::RightPrimaryWeapon:
			if (CustomizeData.RightPrimaryWeaponID != CurrentWeaponData.ID)
			{
				CustomizeData.RightPrimaryWeaponID = CurrentWeaponData.ID;
				Mannequin->EquipWeapon(CurrentPartType, CurrentWeaponData);
				SetEquippedSignVisiblity(true);
				CheckCustomizeComplete();
			}
			break;
		case EMechCustomizePart::LeftShoulderWeapon:
			if (CustomizeData.LeftShoulderWeaponID != CurrentWeaponData.ID)
			{
				CustomizeData.LeftShoulderWeaponID = CurrentWeaponData.ID;
				Mannequin->EquipWeapon(CurrentPartType, CurrentWeaponData);
				SetEquippedSignVisiblity(true);
				CheckCustomizeComplete();
			}
			break;
		case EMechCustomizePart::RightShoulderWeapon:
			if (CustomizeData.RightShoulderWeaponID != CurrentWeaponData.ID)
			{
				CustomizeData.RightShoulderWeaponID = CurrentWeaponData.ID;
				Mannequin->EquipWeapon(CurrentPartType, CurrentWeaponData);
				SetEquippedSignVisiblity(true);
				CheckCustomizeComplete();
			}
			break;
		default:
			break;
		}
		return FReply::Handled();
	}

	if (InKeyEvent.GetKey() == EKeys::Up)
	{
		CurrentPartIndex -= 1;
		if (CurrentPartIndex < 0)
		{
			CurrentPartIndex = CustomizePartArray.Num() - 1;
		}
		CurrentPartType = CustomizePartArray[CurrentPartIndex];
		const FPMWeaponData& CurrentWeaponData = GetCurrentWeaponData();
		UpdateScreenData(CurrentWeaponData, CurrentPartType);

	}

	if (InKeyEvent.GetKey() == EKeys::Down)
	{
		CurrentPartIndex += 1;
		if (CurrentPartIndex >= CustomizePartArray.Num())
		{
			CurrentPartIndex = 0;
		}
		CurrentPartType = CustomizePartArray[CurrentPartIndex];
		const FPMWeaponData& CurrentWeaponData = GetCurrentWeaponData();
		UpdateScreenData(CurrentWeaponData, CurrentPartType);

	}

	if (InKeyEvent.GetKey() == EKeys::Left)
	{
		CurrentIndex -= 1;
		if (CurrentIndex < 0)
		{
			switch (CurrentPartType)
			{
			case EMechCustomizePart::LeftPrimaryWeapon:
				UE_LOG(LogTemp, Warning, TEXT("Matched Case: LeftPrimaryWeapon"));
				CurrentIndex = PrimaryWeaponDataArray.Num() - 1;
				break;
			case EMechCustomizePart::RightPrimaryWeapon:
				UE_LOG(LogTemp, Warning, TEXT("Matched Case: RightPrimaryWeapon"));
				CurrentIndex = PrimaryWeaponDataArray.Num() - 1;
				break;
			case EMechCustomizePart::LeftShoulderWeapon:
				UE_LOG(LogTemp, Warning, TEXT("Matched Case: LeftShoulderWeapon"));

				CurrentIndex = ShoulderWeaponDataArray.Num() - 1;
				break;
			case EMechCustomizePart::RightShoulderWeapon:
				UE_LOG(LogTemp, Warning, TEXT("Matched Case: RightShoulderWeapon"));
				CurrentIndex = ShoulderWeaponDataArray.Num() - 1;
				break;
			default:
				UE_LOG(LogTemp, Error, TEXT("No Matching Case!"));
				break;
			}
		}

		const FPMWeaponData& CurrentWeaponData = GetCurrentWeaponData();
		UpdateScreenData(CurrentWeaponData, CurrentPartType);
	}

	if (InKeyEvent.GetKey() == EKeys::Right)
	{
		CurrentIndex += 1;

		switch (CurrentPartType)
		{
		case EMechCustomizePart::LeftPrimaryWeapon:
			if (CurrentIndex >= PrimaryWeaponDataArray.Num())
			{
				CurrentIndex = 0;
			}
			break;
		case EMechCustomizePart::RightPrimaryWeapon:
			if (CurrentIndex >= PrimaryWeaponDataArray.Num())
			{
				CurrentIndex = 0;
			}
			break;
		case EMechCustomizePart::LeftShoulderWeapon:
			if (CurrentIndex >= ShoulderWeaponDataArray.Num())
			{
				CurrentIndex = 0;
			}
			break;
		case EMechCustomizePart::RightShoulderWeapon:
			if (CurrentIndex >= ShoulderWeaponDataArray.Num())
			{
				CurrentIndex = 0;
			}
			break;
		default:
			break;
		}
		const FPMWeaponData& CurrentWeaponData = GetCurrentWeaponData();
		UpdateScreenData(CurrentWeaponData, CurrentPartType);
	}

	return FReply::Unhandled();
}

void UPMWeaponCustomizing::OnRollOutButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("ROLL OUT!"));
	UPMGameInstance* GameInstance = Cast<UPMGameInstance>(GetGameInstance());
	GameInstance->SetMechCustomizeData(CustomizeData);
	//GameInstance->ActivateLoadingScreen();
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			UGameplayStatics::OpenLevel(GetWorld(), FName("NewMap"));

		});

	//UGameplayStatics::OpenLevel(GetWorld(), FName("DesertLevel"));
	//TODO: 비동기 로딩 스크린 거쳐서 레벨 이동
}

bool UPMWeaponCustomizing::CheckCustomizeComplete()
{
	if (!CustomizeData.LeftPrimaryWeaponID.IsNone() && !CustomizeData.RightPrimaryWeaponID.IsNone() &&
		!CustomizeData.LeftShoulderWeaponID.IsNone() && !CustomizeData.RightShoulderWeaponID.IsNone())
	{
		_RollOutButton->SetIsEnabled(true);
		return true;
	}
	else
	{
		_RollOutButton->SetIsEnabled(false);
		return false;
	}
}
