// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PMEffectPlayer.generated.h"

UCLASS()
class PROJECTMECH_API APMEffectPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APMEffectPlayer();

	void SetVolume(float InVolume);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnParticleFinished(UParticleSystemComponent* PSystem);
	void OnSoundFinished();
public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TObjectPtr<UParticleSystem> ParticleEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TObjectPtr<USoundBase> SoundEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	TObjectPtr<UParticleSystemComponent> SpawnedParticle;

	UPROPERTY()
	TObjectPtr<UAudioComponent> SpawnedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSilence;
	

protected:
	bool IsEffectFinished;
	bool IsSoundFinished;
	FTimerHandle DestroyTimerHandle;
};
