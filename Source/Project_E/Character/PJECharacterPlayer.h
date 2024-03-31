// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJECharacterBase.h"
#include "Interface/PJECharacterItemInterface.h"
#include "PJECharacterPlayer.generated.h"

class IPJEInteractInterface;
class UBoxComponent;
class UInputAction;



UCLASS()
class PROJECT_E_API APJECharacterPlayer : public APJECharacterBase/*, public IABCharacterHUDInterface*/, public IPJECharacterItemInterface
{
	GENERATED_BODY()
public:
	APJECharacterPlayer();
	
	void GetItem(int32 ItemCode);
	FORCEINLINE int32 GetHandItemCode() const { return HandItemCode; }
	// INLINE Function for test.. to be Deleted
	FORCEINLINE void SetHandItemCode(int32 ItemCode) { HandItemCode = ItemCode; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetDead() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnInteractBegin();
	void OnInteractEnd();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	IPJEInteractInterface* GetClosestInterface();
	
	// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere)
	float RaycastTargetLength = 100.0f;

public:
	virtual FVector GetTargetPosition(ECollisionChannel Channel, float RayCastDistance);

	// Input Section
protected:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* MoveAction;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	// UI Section
protected:
	//virtual void SetupHUDWidget(class UABHUDWidget* InHUDWidget) override;

	void ShowPopUI();
	void Attack();

 //Item Section
protected:
	virtual void TakeItem() override;

	UPROPERTY(EditAnywhere, Category = "UI")
	float PopupDistance;

	UPROPERTY(EditAnywhere)
	int32 HandItemCode = 0;

//Interact Section
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> Volume;

	// Crash occurs when UPROPERTY added (reason unknown)
	TObjectPtr<IPJEInteractInterface> Interface;
};