// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PMStatComponent.h"
//
//// Sets default values for this component's properties
//UPMStatComponent::UPMStatComponent()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}
//
//
//// Called when the game starts
//void UPMStatComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}
//
//
//// Called every frame
//void UPMStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}
//

void UPMStatComponent::IncreaseCurrentAP(int32 InIncreaseAmount)
{
	int32 CalculatedAP = CurrentAP + InIncreaseAmount;
	CurrentAP = (CalculatedAP <= MaxAP) ? CalculatedAP : MaxAP;
}

void UPMStatComponent::DecreaseCurrentAP(int32 InDecreaseAmount)
{
	int32 CalculatedAP = CurrentAP - InDecreaseAmount;
	CurrentAP = (CalculatedAP >= 0) ? CalculatedAP : 0;
}

void UPMStatComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentAP = MaxAP;
	CurrentEN = MaxEN;

	OnStatInitialized.Broadcast();
}

void UPMStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}
