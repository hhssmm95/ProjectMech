// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PMMinionBase.h"

// Sets default values
APMMinionBase::APMMinionBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APMMinionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

float APMMinionBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

// Called every frame
void APMMinionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APMMinionBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float APMMinionBase::ApplyDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

