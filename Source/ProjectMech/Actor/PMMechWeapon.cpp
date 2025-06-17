// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PMMechWeapon.h"
#include "Actor/PMProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/StaticMeshSocket.h"
#include "PMEffectPlayer.h"


APMMechWeapon::APMMechWeapon()
{
    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    SetRootComponent(WeaponMesh);
    WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
    MuzzleFlashEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MuzzleFlash"));
    MuzzleFlashEffect->SetupAttachment(RootComponent);
}

void APMMechWeapon::InitializeWeaponData(const FPMWeaponData& InWeaponData, FName TeamTag)
{
    WeaponData = InWeaponData;

    UStaticMesh* LoadedObject = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *InWeaponData.WeaponMeshPath.ToString()));
    WeaponMesh->SetStaticMesh(LoadedObject);

    ProjectileClass = LoadClass<APMProjectile>(nullptr, *(WeaponData.ProjectilePath.ToString() + FString("_C")));
    EffectPlayerClass = LoadClass<APMEffectPlayer>(nullptr, *(WeaponData.FireEffectPath.ToString() + FString("_C")));

    RestAmmo = InWeaponData.MaxMagazine;
    OnWeaponFired.Broadcast(FText::AsNumber(RestAmmo));

    bIsReloaded = true;
    bIsInitialized = true;

    Tags.Add(TeamTag);
}

void APMMechWeapon::Shot(FVector LockedLocation)
{
    if (bIsReloaded && RestAmmo > 0)
    {
        FVector FixedLocation(LockedLocation.X, LockedLocation.Y, LockedLocation.Z + 50);

        FVector SpawnLocation = WeaponMesh->GetSocketLocation(FName("Muzzle"));
        FRotator SocketRotation = WeaponMesh->GetSocketRotation(FName("Muzzle"));

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        SpawnParams.bNoFail = true;
        SpawnParams.Instigator = Cast<APawn>(GetOwner());
        SpawnParams.Owner = GetOwner();

        FRotator BulletRot = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, FixedLocation);

        if (!ProjectileClass)
        {
            ProjectileClass = LoadClass<APMProjectile>(nullptr, *(WeaponData.ProjectilePath.ToString() + FString("_C")));
        }
        APMProjectile* Bullet = GetWorld()->SpawnActor<APMProjectile>(ProjectileClass, SpawnLocation, BulletRot, SpawnParams);
        if (Bullet)
        {
            Bullet->InitializeProjectileData(WeaponData, Tags[0]);
            UE_LOG(LogTemp, Warning, TEXT("Projectile fired! -> LockedLocation : %f, %f, %f"), LockedLocation.X, LockedLocation.Y, LockedLocation.Z);
        }

        if (!EffectPlayerClass)
        {
            EffectPlayerClass = LoadClass<APMEffectPlayer>(nullptr, *(WeaponData.FireEffectPath.ToString() + FString("_C")));
        }
        APMEffectPlayer* MuzzleFlashEffectPlayer = GetWorld()->SpawnActor<APMEffectPlayer>(EffectPlayerClass, SpawnLocation, SocketRotation, SpawnParams);

        RestAmmo -= 1;

        OnWeaponFired.Broadcast(FText::AsNumber(RestAmmo));

        bIsReloaded = false;
        GetWorld()->GetTimerManager().SetTimer(FireRateHandle, FTimerDelegate::CreateLambda([this]()
            {
                bIsReloaded = true;
                UE_LOG(LogTemp, Warning, TEXT("%s Reloading"), *GetName());
            }), WeaponData.ReloadTime, false);

    }

}
