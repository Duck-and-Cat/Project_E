// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_SpawnShockWave.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Project_E/AI/Enemies/PJEShokeWave.h"

UBTTask_SpawnShockWave::UBTTask_SpawnShockWave()
{
    NodeName = "Spawn ShockWave";
}

EBTNodeResult::Type UBTTask_SpawnShockWave::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;

    if (ControlledPawn && ShockWaveClass)
    {
        FVector SpawnLocation = ControlledPawn->GetActorLocation();
        FRotator SpawnRotation = ControlledPawn->GetActorRotation();

        APJEShockwave* SpawnedShockWave = GetWorld()->SpawnActor<APJEShockwave>(ShockWaveClass, SpawnLocation, SpawnRotation);

        if (SpawnedShockWave)
        {
            return EBTNodeResult::Succeeded;
        }
        else
        {
            return EBTNodeResult::Failed;
        }
    }

    return EBTNodeResult::Failed;
}

