// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEMagneticBall.h"
#include "Components/SphereComponent.h"

// Sets default values
APJEMagneticBall::APJEMagneticBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = ColliderComponent;
}

// Called when the game starts or when spawned
void APJEMagneticBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APJEMagneticBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APJEMagneticBall::SetCurrentState(EMagneticBallState NewState)
{
}