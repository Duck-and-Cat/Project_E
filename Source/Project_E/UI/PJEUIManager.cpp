// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJEUIManager.h"
#include "PJEUIManager.h"
#include "GameFramework/PlayerController.h"

UPJEUIManager* UPJEUIManager::Instance = nullptr;

UPJEUIManager* UPJEUIManager::GetInstance()
{
    if (Instance == nullptr)
    {
        Instance = NewObject<UPJEUIManager>();
        Instance->AddToRoot();
    }
    return Instance;
}

UUserWidget* UPJEUIManager::ShowPopupUI(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            UUserWidget* NewWidget = CreateWidget<UUserWidget>(World, WidgetClass);
            if (NewWidget)
            {
                NewWidget->AddToViewport();

                AddPopupWidget(NewWidget);
                ShowTopmostWidget(NewWidget);

                return NewWidget;
            }
        }
    }
    return nullptr;
}

void UPJEUIManager::AddPopupWidget(UUserWidget* NewWidget)
{
    if (NewWidget && !PopupWidgets.Contains(NewWidget))
    {
        PopupWidgets.Add(NewWidget);
    }
}

void UPJEUIManager::RemovePopupWidget(UUserWidget* WidgetToRemove)
{
    if (WidgetToRemove)
    {
        PopupWidgets.Remove(WidgetToRemove);

        if (WidgetToRemove == TopmostWidget)
        {
            TopmostWidget = PopupWidgets.Num() > 0 ? PopupWidgets.Last() : nullptr;
            if (TopmostWidget)
            {
                ShowTopmostWidget(TopmostWidget);
            }
        }
    }
}

UUserWidget* UPJEUIManager::GetTopmostWidget() const
{
    return TopmostWidget;
}

void UPJEUIManager::ShowTopmostWidget(UUserWidget* NewTopmostWidget)
{
    if (NewTopmostWidget)
    {
        NewTopmostWidget->SetVisibility(ESlateVisibility::Visible);

        for (UUserWidget* Widget : PopupWidgets)
        {
            if (Widget && Widget != NewTopmostWidget)
            {
                Widget->SetVisibility(ESlateVisibility::HitTestInvisible);
            }
        }

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = true;
            PlayerController->SetInputMode(FInputModeUIOnly().SetWidgetToFocus(NewTopmostWidget->TakeWidget()));

            NewTopmostWidget->SetKeyboardFocus();
        }

        TopmostWidget = NewTopmostWidget;
    }
}
