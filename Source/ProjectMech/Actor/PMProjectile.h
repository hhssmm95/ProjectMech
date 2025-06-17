// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameConstants.h"
#include "../Actor/PMMechWeapon.h"
#include "PMProjectile.generated.h"

//UENUM(BlueprintType)
//enum class EProjectileType : uint8
//{
//	None,
//	Bullet,
//	Explosive,
//	Laser
//
//};

UCLASS()
class PROJECTMECH_API APMProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APMProjectile();

	//FORCEINLINE void SetTeamTag(ETeamType InTeamTag) { TeamTag = InTeamTag; }
	UFUNCTION()
	void InitializeProjectileData(const FPMWeaponData& InWeaponData, FName TeamTag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnDetectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	TObjectPtr<class UCapsuleComponent> CapsuleCollision;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	TObjectPtr<class UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	TSubclassOf<class APMEffectPlayer> HitEffectPlayerClass = nullptr;

	/*UPROPERTY(VisibleAnywhere, Category = "Type")
	EMechWeaponType ProjectileType;*/

	UPROPERTY(VisibleAnywhere, Category = "Type")
	FPMWeaponData WeaponData;

	float SpawnTime;
	float MaxLifeTime = 3.0f;

protected:

	bool CheckOverlappedActorTags(const AActor* OtherActor);

};
