// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PJEUtils.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UPJEUtils : public UObject
{
	GENERATED_BODY()
	
public:
	template<typename T>
    static T GetRandomElementFromSet(const TSet<T>& Set)
    {
        TArray<T> SetArray = Set.Array();

        if (SetArray.Num() > 0)
        {
            int32 RandomIndex = FMath::RandRange(0, SetArray.Num() - 1);
            return SetArray[RandomIndex];
        }

        return T();
    }
};
