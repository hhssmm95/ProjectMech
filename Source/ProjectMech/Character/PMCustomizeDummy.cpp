// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PMCustomizeDummy.h"
#include "Game/PMGameInstance.h"
#include "Actor/PMMechWeapon.h"

// Sets default values
APMCustomizeDummy::APMCustomizeDummy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    RightArmWeaponSlot = CreateDefaultSubobject <UChildActorComponent>(TEXT("RightArmWeaponSlot"));
    RightArmWeaponSlot->SetupAttachment(GetMesh());


    LeftArmWeaponSlot = CreateDefaultSubobject <UChildActorComponent>(TEXT("LeftArmWeaponSlot"));
    LeftArmWeaponSlot->SetupAttachment(GetMesh());


    RightShoulderWeaponSlot = CreateDefaultSubobject <UChildActorComponent>(TEXT("RightShoulderWeaponSlot"));
    RightShoulderWeaponSlot->SetupAttachment(GetMesh());


    LeftShoulderWeaponSlot = CreateDefaultSubobject <UChildActorComponent>(TEXT("LeftShoulderWeaponSlot"));
    LeftShoulderWeaponSlot->SetupAttachment(GetMesh());
}

void APMCustomizeDummy::EquipWeapon(EMechCustomizePart PartName, const FPMWeaponData& InWeaponData)
{
    UPMGameInstance* GameInstance = Cast<UPMGameInstance>(GetGameInstance());

    UDataTable* WeaponDataTable = GameInstance->GetWeaponDataTable();
    FPMWeaponData LeftArmWeaponData;
    FPMWeaponData RightArmWeaponData;
    FPMWeaponData LeftShoulderWeaponData;
    FPMWeaponData RightShoulderWeaponData;
    switch (PartName)
    {
    case EMechCustomizePart::None:
        return;
        break;
    case EMechCustomizePart::LeftPrimaryWeapon:
        LeftArmWeaponData = InWeaponData;
        

        LeftArmWeapon = Cast<APMMechWeapon>(LeftArmWeaponSlot->GetChildActor());
        if (LeftArmWeapon)
        {
            LeftArmWeapon->InitializeWeaponData(LeftArmWeaponData, Tags[0]);
            LeftArmWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftArmWeapon"));
        }

        break;
    case EMechCustomizePart::RightPrimaryWeapon:
        RightArmWeaponData = InWeaponData;

        RightArmWeapon = Cast<APMMechWeapon>(RightArmWeaponSlot->GetChildActor());
        if (RightArmWeapon)
        {
            RightArmWeapon->InitializeWeaponData(RightArmWeaponData, Tags[0]);
            RightArmWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightArmWeapon"));
        }
        break;
    case EMechCustomizePart::LeftShoulderWeapon:

        LeftShoulderWeaponData = InWeaponData;

        LeftShoulderWeapon = Cast<APMMechWeapon>(LeftShoulderWeaponSlot->GetChildActor());
        if (LeftShoulderWeapon)
        {
            LeftShoulderWeapon->InitializeWeaponData(LeftShoulderWeaponData, Tags[0]);
            LeftShoulderWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftShoulderWeapon"));
        }

        break;
    case EMechCustomizePart::RightShoulderWeapon:

        RightShoulderWeaponData = InWeaponData;

        RightShoulderWeapon = Cast<APMMechWeapon>(RightShoulderWeaponSlot->GetChildActor());
        if (RightShoulderWeapon)
        {
            RightShoulderWeapon->InitializeWeaponData(RightShoulderWeaponData, Tags[0]);
            RightShoulderWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightShoulderWeapon"));
        }

        break;
    default:
        break;
    }


}

void APMCustomizeDummy::BeginPlay()
{
    Super::BeginPlay();

    RightArmWeaponSlot->SetChildActorClass(APMMechWeapon::StaticClass());
    RightArmWeaponSlot->CreateChildActor();

    LeftArmWeaponSlot->SetChildActorClass(APMMechWeapon::StaticClass());
    LeftArmWeaponSlot->CreateChildActor();

    RightShoulderWeaponSlot->SetChildActorClass(APMMechWeapon::StaticClass());
    RightShoulderWeaponSlot->CreateChildActor();

    LeftShoulderWeaponSlot->SetChildActorClass(APMMechWeapon::StaticClass());
    LeftShoulderWeaponSlot->CreateChildActor();
}

