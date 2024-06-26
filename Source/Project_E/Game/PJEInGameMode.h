// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/PJEGameModeBase.h"
#include "PJEInGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEInGameMode : public APJEGameModeBase
{
	GENERATED_BODY()

public:
	APJEInGameMode();

protected:
	void SetDefaultPawnClass();
	void SetPlayerControllerClass();
};
