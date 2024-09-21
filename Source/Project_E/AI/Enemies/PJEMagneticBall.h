// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEMagneticBall.generated.h"

class USphereComponent;

enum class EMagneticBallState
{
	Idle,
	Shaking,
	Falling
};

UCLASS()
class PROJECT_E_API APJEMagneticBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJEMagneticBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Component Section
protected:
	UPROPERTY()
	TObjectPtr<USphereComponent> ColliderComponent;

// State Section
protected:
	EMagneticBallState CurrentState;

public:
	void SetCurrentState(EMagneticBallState NewState);

};
