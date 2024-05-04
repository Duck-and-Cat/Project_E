// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterCat.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PJEPlayerController.h"


APJECharacterCat::APJECharacterCat()
{
}

void APJECharacterCat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APJECharacterCat::DoubleJump);
        EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APJECharacterCat::Dash);
        EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &APJECharacterCat::StopDash);
    }
}

void APJECharacterCat::BeginPlay()
{
    Super::BeginPlay();
}

void APJECharacterCat::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
    bFirstJump = true;
    JumpCount = 0;
}

void APJECharacterCat::DoubleJump()
{
    if (bFirstJump)
    {
        bFirstJump = false;
        JumpCount++;
        Jump();
        return;
    }

    else if (!bFirstJump && JumpCount < 2)
    {
        UCharacterMovementComponent* PlayerMovement = GetCharacterMovement();
        if (PlayerMovement)
        {
            FVector Start = GetActorUpVector();
            float DefaultJumpHeight = PlayerMovement->JumpZVelocity;
            FVector End = GetActorLocation() + Start * DefaultJumpHeight;
            LaunchCharacter(End - GetActorLocation(), false, true);
            JumpCount++;
        }
        return;
    }
}

void APJECharacterCat::Dash()
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed *= 2.0f;
    }
}

void APJECharacterCat::StopDash()
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
    }
}

void APJECharacterCat::Attack()
{
    Super::Attack();

}

void APJECharacterCat::Swing()
{
}