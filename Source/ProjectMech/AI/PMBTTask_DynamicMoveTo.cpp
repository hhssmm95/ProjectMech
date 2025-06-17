// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PMBTTask_DynamicMoveTo.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UPMBTTask_DynamicMoveTo::UPMBTTask_DynamicMoveTo()
{
    // 필요시 기본값을 설정할 수 있습니다.
    // 예를 들어, 기존 AcceptableRadius의 기본값 대신 5.0f 등으로 조정 가능
    DefaultAcceptableRadius = 1200.0f;
    AcceptableRadius = DefaultAcceptableRadius;

}

EBTNodeResult::Type UPMBTTask_DynamicMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
    {
        // Blackboard에 "AimAcceptableRadius"라는 Float형 값이 있다고 가정합니다.
        const float DynamicRadius = BlackboardComp->GetValueAsFloat(FName("AimAcceptableRadius"));

        // 디버그 로그로 값 확인 (옵션)
        //UE_LOG(LogTemp, Log, TEXT("DynamicRadius from Blackboard: %f"), DynamicRadius);

        // Move To 태스크에 사용되는 AcceptableRadius 값을 덮어씁니다.
        AcceptableRadius = DynamicRadius;

        UE_LOG(LogTemp, Warning, TEXT("DynamicRadius : %f"), DynamicRadius);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BlackboardComponent is null in PMBTTask_DynamicMoveTo!"));
    }

    // 기본 Move To 태스크의 ExecuteTask 로직을 실행합니다.
    return Super::ExecuteTask(OwnerComp, NodeMemory);
}
