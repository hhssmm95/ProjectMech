// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PMAnimInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAimOffsetMode : uint8
{
	Normal,
	LockOn
};

UCLASS()
class PROJECTMECH_API UPMAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPMAnimInstance();

public:
	UFUNCTION()
	void SetAimOffsetMode(EAimOffsetMode InAOMode, FVector InTargetPos = FVector(0.f,0.f,0.f));
	
	UFUNCTION(BlueprintCallable)
	void AnimNotify_LeftFoot();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_RightFoot();

	UFUNCTION(BlueprintCallable)
	void SetDeathState();

	UFUNCTION()
	void AnimNotify_EndOfDeath();


	virtual void NativeInitializeAnimation() override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAimOffsetMode CurrentAOMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	bool bIsDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect")
	TSubclassOf<class APMEffectPlayer> FootSoundPlayerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect")
	TSubclassOf<class APMEffectPlayer> ExplosionEffectClass;

	TObjectPtr<class APMMechBase> OwnerMech;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage")
	TObjectPtr<UAnimMontage> DeathMontage;

};
