// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "PJEUIManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UPJEUIManager : public UObject
{
    GENERATED_BODY()

public:
    static UPJEUIManager* GetInstance();

    UUserWidget* ShowPopupUI(TSubclassOf<UUserWidget> WidgetClass);
    void ShowTopmostWidget(UUserWidget* NewTopmostWidget);
    void AddPopupWidget(UUserWidget* NewWidget);
    void RemovePopupWidget(UUserWidget* WidgetToRemove);
    UUserWidget* GetTopmostWidget() const;

private:
    UPJEUIManager() {}  // Private constructor for singleton pattern
    static UPJEUIManager* Instance;

    TArray<TObjectPtr<UUserWidget>> PopupWidgets;
    TObjectPtr<UUserWidget> TopmostWidget = nullptr;
};
