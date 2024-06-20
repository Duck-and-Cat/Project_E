// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJEInteractInterface.h"
#include "GameFramework/Actor.h"
#include "PJEButtonBase.generated.h"

class UWidgetComponent;
class APJEPlatform;
class UBoxComponent;

UCLASS()
class PROJECT_E_API APJEButtonBase : public AActor, public IPJEInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJEButtonBase();

protected:
	virtual void BeginPlay() override;

	void CheckButtonActive(float DeltaTime);
	
	void NotifyActiveToPlatform(bool ButtonActive);

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	bool bButtonActive = false;

protected:
	virtual void ShowInteractWidget() override;
	virtual void HideInteractWidget() override;

	virtual void BeginInteracting(const AActor* InteractActor) override;
	virtual void EndInteracting(const AActor* InteractActor) override;

protected:
	// Button Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ButtonTrigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonBorderMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> WidgetTrigger;
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector OriginLocation;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveOffset;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveTime;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<APJEPlatform>> Platforms;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* Widget;
};
