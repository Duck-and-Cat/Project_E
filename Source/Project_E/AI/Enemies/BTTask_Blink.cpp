// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask_Blink.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAI.h"
#include "Project_E/Character/PJECharacterShadowA.h"
#include "Project_E/AI/PJEAIController.h"

UBTTask_Blink::UBTTask_Blink()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Blink::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

    APJEAIController* OwnerController = Cast<APJEAIController>(OwnerComp.GetOwner());

    APJECharacterShadowA* OwnerActor = Cast<APJECharacterShadowA>(OwnerController->GetPawn());

    FBTBlinkTaskMemory* TaskMemory = (FBTBlinkTaskMemory*)NodeMemory;

    if (TaskMemory != nullptr)
    {
        TaskMemory->TargetActor = OwnerActor;
        TaskMemory->AccumulatedSingleBlinkTime = 0.0f;
        TaskMemory->BlinkStartTime = GetWorld()->GetTimeSeconds();
    }
	return EBTNodeResult::InProgress;
}

void UBTTask_Blink::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    ACharacter* ControlledPawn = Cast<ACharacter>(AICon->GetPawn());
    if (!ControlledPawn)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    USkeletalMeshComponent* Mesh = ControlledPawn->GetMesh();

    FBTBlinkTaskMemory* TaskMemory = (FBTBlinkTaskMemory*)NodeMemory;

    TaskMemory->AccumulatedSingleBlinkTime += DeltaSeconds;

    if (TaskMemory->AccumulatedSingleBlinkTime >= TaskMemory->TargetActor->GetSingleBlinkDuration())
    {

        if (GetWorld()->TimeSeconds - TaskMemory->BlinkStartTime >= TaskMemory->TargetActor->GetBlinkDuration())
        {
            Mesh->SetVisibility(true);
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return;
        }

        Mesh->SetVisibility(!Mesh->IsVisible());
        TaskMemory->AccumulatedSingleBlinkTime -= TaskMemory->TargetActor->GetSingleBlinkDuration();
    }
}

