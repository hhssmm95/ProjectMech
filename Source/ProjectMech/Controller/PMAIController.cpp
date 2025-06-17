// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PMAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"


//APMAIController::APMAIController()
//{
//    PrimaryActorTick.bCanEverTick = true;
//    PrimaryActorTick.bStartWithTickEnabled = true;
//
//    // 0.1초마다 Tick 호출
//    PrimaryActorTick.TickInterval = 0.5f;
//
//}

void APMAIController::UpdateMainTarget(AActor* MainTarget)
{
    if (Blackboard)
    {
        //UE_LOG(LogTemp, Log, TEXT("bIsTargetLocekd Set to : %s"), *LexToString(bIsTargetLocked));
        //Blackboard->SetValueAsBool(TEXT("IsTargetLocked"), bIsTargetLocked);
        // 블랙보드에서 특정 키에 위치 벡터 저장
        Blackboard->SetValueAsObject(TEXT("MainTarget"), MainTarget);
        if (MainTarget)
        {
            TargetMech = MainTarget;
        }
        else
        {
            TargetMech = nullptr;
        }
    }


}

void APMAIController::UpdateTargetLocation(FVector InLocation)
{
    Blackboard->SetValueAsVector(TEXT("TargetLocation"), InLocation);
}

void APMAIController::SetAimAcceptableRadius(float InRadius)
{
    if (Blackboard)
    {
        Blackboard->SetValueAsFloat(TEXT("AimAcceptableRadius"), InRadius);

    }
}

void APMAIController::SetAsSniper(bool IsSniper)
{
    Blackboard->SetValueAsBool(TEXT("IsSniper"), IsSniper);
}

void APMAIController::SetEnableBrainComponent(bool InEnable)
{
    if (InEnable)
    {
        BrainComponent->ResumeLogic("ResumeAI");
    }
    else
    {
        BrainComponent->PauseLogic("PauseAI");
    }
}

void APMAIController::SetIsInAcceptableDist(bool IsInDist)
{
    Blackboard->SetValueAsBool(TEXT("IsInAcceptableDist"), IsInDist);

}

void APMAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (BehaviorTreeAsset && BlackboardData)
    {
        UBlackboardComponent* BlackboardComp = Blackboard;
        // 블랙보드 초기화 및 설정
        UseBlackboard(BlackboardData, BlackboardComp);


        RunBehaviorTree(BehaviorTreeAsset); // Behavior Tree 실행

    }

}

//void APMAIController::Tick(float DeltaTime)
//{
//    if (TargetMech)
//    {
//        Blackboard->SetValueAsVector(TEXT("TargetLocation"), TargetMech->GetActorLocation());
//    }
//}
//
