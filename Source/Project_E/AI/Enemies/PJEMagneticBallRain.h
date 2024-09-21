// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEMagneticBallRain.generated.h"

class APJEMagneticBallRing;
UCLASS()
class PROJECT_E_API APJEMagneticBallRain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJEMagneticBallRain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Ring Section
protected:
	TObjectPtr<APJEMagneticBallRing> Rings[3];
};
