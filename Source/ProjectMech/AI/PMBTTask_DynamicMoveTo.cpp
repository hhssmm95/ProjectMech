// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PMBTTask_DynamicMoveTo.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UPMBTTask_DynamicMoveTo::UPMBTTask_DynamicMoveTo()
{
    // �ʿ�� �⺻���� ������ �� �ֽ��ϴ�.
    // ���� ���, ���� AcceptableRadius�� �⺻�� ��� 5.0f ������ ���� ����
    DefaultAcceptableRadius = 1200.0f;
    AcceptableRadius = DefaultAcceptableRadius;

}

EBTNodeResult::Type UPMBTTask_DynamicMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
    {
        // Blackboard�� "AimAcceptableRadius"��� Float�� ���� �ִٰ� �����մϴ�.
        const float DynamicRadius = BlackboardComp->GetValueAsFloat(FName("AimAcceptableRadius"));

        // ����� �α׷� �� Ȯ�� (�ɼ�)
        //UE_LOG(LogTemp, Log, TEXT("DynamicRadius from Blackboard: %f"), DynamicRadius);

        // Move To �½�ũ�� ���Ǵ� AcceptableRadius ���� ����ϴ�.
        AcceptableRadius = DynamicRadius;

        UE_LOG(LogTemp, Warning, TEXT("DynamicRadius : %f"), DynamicRadius);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BlackboardComponent is null in PMBTTask_DynamicMoveTo!"));
    }

    // �⺻ Move To �½�ũ�� ExecuteTask ������ �����մϴ�.
    return Super::ExecuteTask(OwnerComp, NodeMemory);
}
