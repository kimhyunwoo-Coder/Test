﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LSMainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ALSMainMenuPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
};
