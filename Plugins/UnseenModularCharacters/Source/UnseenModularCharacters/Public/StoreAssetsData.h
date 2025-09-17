// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "Engine/DataAsset.h"
#include "StoreAssetsData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UNSEENMODULARCHARACTERS_API UStoreAssetsData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Store Items")
	TArray<FItemRarity> StoreItems;
};
