// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterMonster.h"
#include "PJECharacterShadow.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterShadow : public APJECharacterMonster
{
	GENERATED_BODY()
	
public:
	APJECharacterShadow();

// Spawn Section
public:
	FORCEINLINE void SetShadowGeneratorsCount(int32 NewShadowGeneratorsCount);
	FORCEINLINE float GetShadowSpawnRadius() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shadow Generator")
	int32 ShadowGeneratorsCount;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float ShadowSpawnRadius;
};