// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEMagneticBallRing.generated.h"

class APJEMagneticBall;

UCLASS()
class PROJECT_E_API APJEMagneticBallRing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJEMagneticBallRing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Magnetic Ball Section
protected:
	UPROPERTY()
	TSet<TObjectPtr<APJEMagneticBall>> MagneticBalls;

};
