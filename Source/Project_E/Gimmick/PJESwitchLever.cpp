#include "Gimmick/PJESwitchLever.h"

#include "PJERotateComponent.h"

APJESwitchLever::APJESwitchLever()
{
	//LeverBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever Base"));
	//LeverBaseMesh->SetupAttachment(RootComponent);
	//LeverPivot = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("Lever Pivot"));
	//LeverPivot->SetupAttachment(LeverBaseMesh);
	//LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever"));
	//LeverMesh->SetupAttachment(LeverPivot);

	//RotateComponent = CreateDefaultSubobject<UPJERotateComponent>(TEXT("Rotate Component"));
}

void APJESwitchLever::BeginPlay()
{
	Super::BeginPlay();
	//RotateComponent->SetRotateTarget(LeverPivot);
}

void APJESwitchLever::InteractionKeyReleased()
{
	Super::InteractionKeyReleased();

	ActivateLever();
}

void APJESwitchLever::ActivateLever()
{
	if(!bIsActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lever On"));
		bIsActive = true;
		//RotateComponent->SetRotateState(ERotateState::Rotating);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lever Off"));
		bIsActive = false;
		//RotateComponent->SetRotateState(ERotateState::Returning);
	}
}

void APJESwitchLever::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
