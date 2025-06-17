// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PMAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/PMEffectPlayer.h"
#include "PMMechBase.h"
#include "GameFramework/Character.h"
#include "Game/PMGameModeBase.h"

UPMAnimInstance::UPMAnimInstance()
{
}

void UPMAnimInstance::SetAimOffsetMode(EAimOffsetMode InAOMode, FVector InTargetPos)
{
	switch (InAOMode)
	{
	case EAimOffsetMode::Normal:
		break;
	case EAimOffsetMode::LockOn:
		//GetOwningActor()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetOwningActor()->GetActorLocation(), InTargetPos));
		/*
		* TODO: 대상과 180도 이상 차이나면 대상 즉시 쳐다보도록
		*/
		break;
	default:
		break;
	}
	CurrentAOMode = InAOMode;
}

void UPMAnimInstance::AnimNotify_LeftFoot()
{
	UE_LOG(LogTemp, Log, TEXT("AnimNotify_LeftPlant"));
        
	if (FootSoundPlayerClass && OwnerMech)
	{
		USkeletalMeshComponent* MeshComp = OwnerMech->GetMesh();
		if (MeshComp)
		{
			FVector SpawnLocation = MeshComp->GetSocketLocation(FName("Foot_L"));
			FRotator SocketRotation = MeshComp->GetSocketRotation(FName("MFoot_L"));
			FActorSpawnParameters SpawnParams;
			APMEffectPlayer* EffectPlayer = GetWorld()->SpawnActor<APMEffectPlayer>(FootSoundPlayerClass, SpawnLocation, SocketRotation, SpawnParams);
			if (!OwnerMech->GetIsPlayerMech())
			{
				EffectPlayer->SetVolume(0.1f);
			}
		}
	}

}

void UPMAnimInstance::AnimNotify_RightFoot()
{
	UE_LOG(LogTemp, Log, TEXT("AnimNotify_RightPlant"));
	if (FootSoundPlayerClass && OwnerMech)
	{
		USkeletalMeshComponent* MeshComp = OwnerMech->GetMesh();
		if (MeshComp)
		{
			FVector SpawnLocation = MeshComp->GetSocketLocation(FName("Foot_R"));
			FRotator SocketRotation = MeshComp->GetSocketRotation(FName("Foot_R"));
			FActorSpawnParameters SpawnParams;
			APMEffectPlayer* EffectPlayer = GetWorld()->SpawnActor<APMEffectPlayer>(FootSoundPlayerClass, SpawnLocation, SocketRotation, SpawnParams);
			if (!OwnerMech->GetIsPlayerMech())
			{
				EffectPlayer->SetVolume(0.1f);
			}
		}
	}
}

void UPMAnimInstance::SetDeathState()
{
	bIsDead = true;

}

void UPMAnimInstance::AnimNotify_EndOfDeath()
{
	/*USkeletalMeshComponent* MeshComp = OwnerCharacter->GetMesh();
	MeshComp->bPauseAnims = true;*/

	UE_LOG(LogTemp, Log, TEXT("AnimNotify_EndOfDeath"));
	if (OwnerMech)
	{
		USkeletalMeshComponent* MeshComp = OwnerMech->GetMesh();
		if (MeshComp)
		{
			FVector SpawnLocation1 = MeshComp->GetSocketLocation(FName("Chest"));
			FRotator SocketRotation1 = MeshComp->GetSocketRotation(FName("Chest"));
			FActorSpawnParameters SpawnParams;
			APMEffectPlayer* EffectPlayer1 = GetWorld()->SpawnActor<APMEffectPlayer>(ExplosionEffectClass, SpawnLocation1, SocketRotation1, SpawnParams);


			FVector SpawnLocation2 = MeshComp->GetSocketLocation(FName("FX_Head"));
			FRotator SocketRotation2 = MeshComp->GetSocketRotation(FName("FX_Head"));
			APMEffectPlayer* EffectPlayer2 = GetWorld()->SpawnActor<APMEffectPlayer>(ExplosionEffectClass, SpawnLocation2, SocketRotation2, SpawnParams);
		}
		if (OwnerMech->GetIsPlayerMech())
		{
			OwnerMech->HandleDefeat();
		}
		else
		{
			APMGameModeBase* GameMode = Cast<APMGameModeBase>(GetWorld()->GetAuthGameMode());
			GameMode->DecreaseEnemyCount();
		}
		OwnerMech->ApplyDeath();
	}
}

void UPMAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* PawnOwner = TryGetPawnOwner();
	if (PawnOwner)
	{
		OwnerMech = Cast<APMMechBase>(PawnOwner);
	}

}


