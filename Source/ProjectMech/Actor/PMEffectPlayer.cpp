// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PMEffectPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
APMEffectPlayer::APMEffectPlayer()
{

}

void APMEffectPlayer::SetVolume(float InVolume)
{
    if (SpawnedSound)
    {
        SpawnedSound->SetVolumeMultiplier(InVolume);
    }
}

// Called when the game starts or when spawned
void APMEffectPlayer::BeginPlay()
{
	Super::BeginPlay();

    if (ParticleEffect)
    {
        SpawnedParticle = UGameplayStatics::SpawnEmitterAttached(ParticleEffect, GetRootComponent());

        if (SpawnedParticle)
        {
            SpawnedParticle->OnSystemFinished.AddDynamic(this, &APMEffectPlayer::OnParticleFinished);
        }
    }
    else
    {
        IsEffectFinished = true;
    }


    float SoundDuration = 0.0f;
    if (SoundEffect)
    {
        SoundDuration = SoundEffect->GetDuration();
        SpawnedSound = UGameplayStatics::SpawnSoundAttached(SoundEffect, GetRootComponent());
        if (bSilence)
        {
            SetVolume(0.0f);
        }
        if (SoundDuration > 0.0f)
        {
            GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &APMEffectPlayer::OnSoundFinished, SoundDuration, false);
        }
    }
    else
    {
        IsSoundFinished = true;
    }

    

}

void APMEffectPlayer::OnParticleFinished(UParticleSystemComponent* PSystem)
{
    IsEffectFinished = true;
    if (IsSoundFinished)
    {
        Destroy();
    }
}

void APMEffectPlayer::OnSoundFinished()
{
    IsSoundFinished = true;
    if (IsEffectFinished)
    {
        Destroy();
    }
}