// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "../Items/Inventory.h"
#include <Interface/PJEGameInterface.h>
#include "Components/BoxComponent.h"
#include "Game/PJEGameModeBase.h"
#include "Gimmick/PJEInteractInterface.h"

APJECharacterPlayer::APJECharacterPlayer()
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetMesh());
    CameraBoom->TargetArmLength = 600.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
    Volume->SetupAttachment(RootComponent);
}

bool APJECharacterPlayer::GetItem(int32 ItemCode)
{
    //주석확인용
    if (Inventory && !Inventory->IsFull())
    {
        UDataTable* ItemDatabase = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/itemData.itemData"));

        UItem* NewItem = UItem::SetItem(ItemDatabase, ItemCode); 
        if (NewItem)
        {
            Inventory->AddItem(NewItem);
            return true;
        }
    }

    return false;

    // Please implement ^~^
    // a. ItemCode is the code assigned to each item.
    // b. When the player's GetItem() is executed on class DroppedItem, the ItemCode is passed by argument.
    // c. Return false if it is impossible to get the item ( ex) inventory is full )
    // d. Return true if the item can be picked up
}

void APJECharacterPlayer::BeginPlay()
{
    Super::BeginPlay();

    Inventory = NewObject<UInventory>(this);

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        EnableInput(PlayerController);
    }

    InputComponent->BindAction("Interact", IE_Pressed, this, &APJECharacterPlayer::OnInteractBegin);
    InputComponent->BindAction("Interact", IE_Released, this, &APJECharacterPlayer::OnInteractEnd);

    Volume->OnComponentBeginOverlap.AddDynamic(this, &APJECharacterPlayer::OnOverlapBegin);
    Volume->OnComponentEndOverlap.AddDynamic(this, &APJECharacterPlayer::OnOverlapEnd);
}

void APJECharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultContext, 0);
        }
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APJECharacterPlayer::OnMove);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APJECharacterPlayer::OnLook);
        //EnhancedInputComponent->BindAction(TakeAction, ETriggerEvent::Triggered, this, &APJECharacterPlayer::TakeItem);
    }
}

void APJECharacterPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(Interface)
    {
        Interface->HideInteracPointWidget();
    }
    
    Interface = GetClosestInterface();
    
    if(Interface)
    {
        Interface->ShowInteractPointWidget();    
    }
}

FVector APJECharacterPlayer::GetTargetPosition(ECollisionChannel Channel, float RayCastDistance)
{
    FVector CameraLocation;
    FRotator CameraRotation;

    if (Controller)
    {
        Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);
    }

    FVector Start = CameraLocation;
    FVector End = Start + (CameraRotation.Vector() * RayCastDistance);

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, Channel, CollisionParams))
    {
        if (HitResult.GetActor() && HitResult.GetActor()->IsA<APJECharacterBase>())
        {
            APJECharacterBase* TargetCharacter = Cast<APJECharacterBase>(HitResult.GetActor());
            if (TargetCharacter && TargetCharacter->IsTarget)
            {
                return FVector(HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z);
            }
        }
    }

    return End;
}



void APJECharacterPlayer::SetDead()
{
    Super::SetDead();

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        DisableInput(PlayerController);

        IPJEGameInterface* ABGameMode = Cast<IPJEGameInterface>(GetWorld()->GetAuthGameMode());
        if (ABGameMode)
        {
            ABGameMode->OnPlayerDead(0/*PlayerNumber*/);
        }
    }
}



void APJECharacterPlayer::OnMove(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    Move(MovementVector);
}

void APJECharacterPlayer::OnLook(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();
    Look(LookAxisVector);
}


void APJECharacterPlayer::ShowPopUI()
{
    FVector TargetPosition = GetTargetPosition(ECollisionChannel::ECC_GameTraceChannel1, 100.0f);

    if (TargetPosition != FVector::ZeroVector)
    {
        APlayerController* PlayerController = Cast<APlayerController>(GetController());
        if (PlayerController)
        {
            IPJEGameInterface* ABGameMode = Cast<IPJEGameInterface>(GetWorld()->GetAuthGameMode());
            if (ABGameMode)
            {
                //ABGameMode->ShowPopupWidget();
            }
        }
    }
}

void APJECharacterPlayer::Attack()
{

}

void APJECharacterPlayer::TakeItem(UItem* Item)
{
    if (Inventory)
    {
        Inventory->AddItem(Item);

        Item->ConditionalBeginDestroy();
    }
}

void APJECharacterPlayer::OnInteractBegin()
{
    if (Interface)
    {
        Interface->BeginInteracting(Cast<AActor>(this));
    }
}

void APJECharacterPlayer::OnInteractEnd()
{
    if (Interface)
    {
        Interface->EndInteracting(Cast<AActor>(this));
    }
}

void APJECharacterPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(IPJEInteractInterface* OtherActorInterface = Cast<IPJEInteractInterface>(OtherActor))
    {
        // If Cast Succeed
        OtherActorInterface->ShowInteractWidget();
    }
}

void APJECharacterPlayer::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if(IPJEInteractInterface* OtherActorInterface = Cast<IPJEInteractInterface>(OtherActor))
    {
        // If Cast Succeed
        OtherActorInterface->HideInteractWidget();
    }
}

IPJEInteractInterface* APJECharacterPlayer::GetClosestInterface()
{
    TArray<AActor*> OverlappingActors;
    TArray<IPJEInteractInterface*> OverlappingInterfaces;
    IPJEInteractInterface* ClosestInterface = nullptr;

    Volume->GetOverlappingActors(OverlappingActors);

    for (auto CurrentActor : OverlappingActors)
    {
        if (IPJEInteractInterface* CInterface = Cast<IPJEInteractInterface>(CurrentActor))
        {
            OverlappingInterfaces.Add(CInterface);
        }
    }

    if (OverlappingInterfaces.IsEmpty())
    {
        return nullptr;
    }

    ClosestInterface = OverlappingInterfaces[0];

    for (auto CurrentInterface : OverlappingInterfaces)
    {
        if (GetDistanceTo(Cast<AActor>(CurrentInterface)) <
            GetDistanceTo(Cast<AActor>(ClosestInterface)))
        {
            ClosestInterface = CurrentInterface;
        }
    }

    return ClosestInterface;
}
