// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "../Interface/Damageable.h"
#include "PMMechBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDetectSucceeded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDetectFailed);


UCLASS()
class PROJECTMECH_API APMMechBase : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APMMechBase();

	float ApplyDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void ApplyDeath();

	UFUNCTION()
	void HandleVictory();
	UFUNCTION()
	void HandleDefeat();
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override; 
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
	void HandleHUDInitialized();

	UFUNCTION()
	void HandleStatInitialized();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);    

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	

public:
	UFUNCTION()
	void UseRightWeapon();
	UFUNCTION()
	void ReleaseRightWeapon();
	UFUNCTION()
	void UseLeftWeapon();
	UFUNCTION()
	void ReleaseLeftWeapon();
	UFUNCTION()
	void UseRightShoulderWeapon();
	UFUNCTION()
	void ReleaseRightShoulderWeapon();
	UFUNCTION()
	void UseLeftShoulderWeapon();
	UFUNCTION()
	void ReleaseLeftShoulderWeapon();
	
protected:

	UFUNCTION()
	void UpdateLAWeaponAmmoText(FText InAmmoCount);

	UFUNCTION()
	void UpdateLSWeaponAmmoText(FText InAmmoCount);

	UFUNCTION()
	void UpdateRAWeaponAmmoText(FText InAmmoCount);

	UFUNCTION()
	void UpdateRSWeaponAmmoText(FText InAmmoCount);

protected:
	void Detect(); 
	bool IsInFieldOfView(const AActor* Target);
	UFUNCTION()
	void OnDetectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDetectEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FOnDetectSucceeded OnDetectSucceeded;
	FOnDetectFailed OnDetectFailed;

	// Component Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPMHUDComponent> HUDComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPMStatComponent> StatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detect", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> DetectSphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> RightArmWeaponSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> LeftArmWeaponSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> RightShoulderWeaponSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChildActorComponent> LeftShoulderWeaponSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class APMMechWeapon> RightArmWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class APMMechWeapon> LeftArmWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class APMMechWeapon> RightShoulderWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class APMMechWeapon> LeftShoulderWeapon;

	// Input Section
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RArmWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LArmWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RShoulderWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LShoulderWeaponAction;

	// Camera Section
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Target Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Detect, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AActor>> DetectedTargets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Detect, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AActor>> InSightTargets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Detect, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> MainTarget;

protected:
	UPROPERTY()
	bool bIsDetecting;

	UPROPERTY()
	bool bIsTargetLockedOn;


	UPROPERTY()
	bool bIsPlayerMech;


	UPROPERTY()
	bool bIsDead;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", Meta = (AllowPrivateAccess = "true"))
	FName AILeftArmWeaponID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	FName AIRightArmWeaponID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	FName AILeftShoulderWeaponID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = "true"))
	FName AIRightShoulderWeaponID;

	// for AI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	float AimAcceptableDist = 1200.0f;
	// for AI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	bool bIsSniper;
public:
	UFUNCTION(BlueprintCallable)
	bool GetIsTargetLockedOn() { return bIsTargetLockedOn; }


	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentMainTarget() { return MainTarget.Get(); }

	UFUNCTION()
	bool GetIsPlayerMech() { return bIsPlayerMech;  }

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(EMechCustomizePart PartName, FName WeaponID);

};
