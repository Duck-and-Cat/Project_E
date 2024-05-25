// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask_Teleport.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAI.h"
#include "Project_E/Character/PJECharacterShadowA.h"
#include "Project_E/AI/PJEAIController.h"

UBTTask_Teleport::UBTTask_Teleport()
{
    NodeName = "Random Teleport";
}

EBTNodeResult::Type UBTTask_Teleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    

    APJEAIController* OwnerController = Cast<APJEAIController>(OwnerComp.GetOwner());

    APJECharacterShadowA* OwnerActor = Cast<APJECharacterShadowA>(OwnerController->GetPawn());

    FVector CurrentLocation = OwnerActor->GetActorLocation();
    FNavLocation RandomNavLocation;
    float Radius = OwnerActor->GetTeleportRange();

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if (!NavSys)
    {
        return EBTNodeResult::Failed;
    }

    const int32 MaxAttempts = 10;  // �õ� Ƚ�� ����
    int32 Attempts = 0;
    bool bLocationFound = false;

    while (Attempts < MaxAttempts)
    {
        if (NavSys->GetRandomPointInNavigableRadius(CurrentLocation, Radius, RandomNavLocation))
        {
            bLocationFound = true;
            break;
        }

        Attempts++;
    }

    if (!bLocationFound)
    {
        return EBTNodeResult::Failed;
    }

    OwnerActor->SetActorLocation(RandomNavLocation.Location);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISPLAYERNEARBY, false);
    return EBTNodeResult::Succeeded;
}

