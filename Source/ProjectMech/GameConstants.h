// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameConstants.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETeamType : uint8
{
    FRIENDLY UMETA(DisplayName = "FRIENDLY"),
    ENEMY UMETA(DisplayName = "ENEMY"),
};

UENUM(BlueprintType)
enum class EMechPartType : uint8
{
	None,
	Core,
	Thruster,
	PrimaryWeapon,
	ShoulderWeapon,
	FCS
};

UENUM(BlueprintType)
enum class EMechCustomizePart : uint8
{
	None,
	LeftPrimaryWeapon,
	RightPrimaryWeapon,
	LeftShoulderWeapon,
	RightShoulderWeapon

};

UENUM(BlueprintType)
enum class EMechWeaponType : uint8
{
	None,
	Gun,
	GrenadeLauncher,
	Laser,
	Missile

};

USTRUCT(BlueprintType)
struct FPMMechData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RightPrimaryWeaponID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LeftPrimaryWeaponID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RightShoulderWeaponID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LeftShoulderWeaponID;
};

USTRUCT(BlueprintType)
struct FPMWeaponData : public FTableRowBase
{
	GENERATED_BODY()

	//RF1, GL1, LS1 ... etc
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMechPartType MountingPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMechWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxMagazine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//MAX = 1.0
	float GuidePerformance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath WeaponMeshPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath FireEffectPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath ProjectilePath;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Thumbnail;

	/*void operator=(const FPMWeaponData& InData)
	{
		ID = InData.ID;
	}*/
};


namespace GameConstants
{
    constexpr const TCHAR* WeaponDataTablePath = TEXT("/Game/ProjectMech/Data/DT_WeaponData.DT_WeaponData");
	
	constexpr const TCHAR* LoadingScreenWidgetPath = TEXT("/Game/ProjectMech/Blueprint/Widget/WBP_LoadingScreen.WBP_LoadingScreen_C");
}



//class PROJECTMECH_API GameConstants
//{
//public:
//	GameConstants();
//	~GameConstants();
//};
//
