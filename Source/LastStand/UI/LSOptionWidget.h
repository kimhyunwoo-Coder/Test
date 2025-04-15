// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/LSBaseWidget.h"
#include "LSOptionWidget.generated.h"

class USlider;
class UTextBlock;

UCLASS()
class LASTSTAND_API ULSOptionWidget : public ULSBaseWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;


    UFUNCTION()
    void OnMasterVolumeChanged(float Value);

    UFUNCTION()
    void OnSaveClicked();

    UFUNCTION()
    void OnResetClicked();

    float TempMasterVolume = 1.0f;

    UPROPERTY(meta = (BindWidget))
    USlider* MasterVolumeSlider;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* VolumeText;

    UPROPERTY(meta = (BindWidget))
    UButton* SaveButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetButton;
};
