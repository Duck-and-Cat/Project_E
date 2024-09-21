// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SpawnShockWave.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_SpawnShockWave : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SpawnShockWave();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShockWave")
	TSubclassOf<class APJEShockwave> ShockWaveClass;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
