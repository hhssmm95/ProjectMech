// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PMBTTask_Attack.h"
#include "Controller/PMAIController.h"
#include "Character/PMMechBase.h"

UPMBTTask_Attack::UPMBTTask_Attack()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UPMBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APMAIController* AIController = Cast< APMAIController>(OwnerComp.GetAIOwner());
    if (!AIController) return EBTNodeResult::Failed;

    APMMechBase* AIMech = Cast<APMMechBase>(AIController->GetPawn());
    if (!AIMech) return EBTNodeResult::Failed;

    AIMech->UseLeftWeapon();
    AIMech->UseRightWeapon();
    AIMech->UseLeftShoulderWeapon();
    AIMech->UseRightShoulderWeapon();


    return EBTNodeResult::Succeeded;
}
