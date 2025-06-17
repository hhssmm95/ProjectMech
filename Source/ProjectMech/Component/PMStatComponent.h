// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PMStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatInitialized);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTMECH_API UPMStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetMaxAP(int32 InMaxAP) { MaxAP = InMaxAP; }
	FORCEINLINE int32 GetMaxAP() { return MaxAP; }
	FORCEINLINE void SetCurrentAP(int32 InCurrentAP) { CurrentAP = InCurrentAP; }
	FORCEINLINE int32 GetCurrentAP() { return CurrentAP; }

public:
	UFUNCTION()
	void IncreaseCurrentAP(int32 InIncreaseAmount);

	UFUNCTION()
	void DecreaseCurrentAP(int32 InDecreaseAmount);

public:
	FOnStatInitialized OnStatInitialized;

protected:
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"));
	int32 MaxAP;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat);
	int32 CurrentAP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"));
	int32 MaxEN;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat);
	int32 CurrentEN;
};
