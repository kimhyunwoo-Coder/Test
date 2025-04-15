﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LSLoginSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEOSLoginComplete);

UCLASS()
class LASTSTAND_API ULSLoginSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "LSEOSSubsystem")
    void LoginWithEOS(const FString& UserId, const FString& Token, const FString& LoginType);
    UFUNCTION(BlueprintCallable, Category = "LSEOSSubsystem")
    void GetPlayerUse(const FString& UserId, const FString& Token, const FString& LoginType);
    UFUNCTION(BlueprintCallable, Category = "LSEOSSubsystem")
    bool GetIsPlayerLogin();
    
private:
    void LoginWithEOSComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorString);

public:
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "LSEOSSubsystem")
    FOnEOSLoginComplete OnEOSLoginComplete;
    FDelegateHandle LoginDelegateHandle;
};
