// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameTypes.h"
#include "NftDropData.generated.h"

class UUnseenAssetData;



/**
 * 
 */
UCLASS(Blueprintable)
class UNSEENMODULARCHARACTERS_API UNftDropData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Drop Data")
	int StartingIndex = -1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Drop Data")
	TArray<UUnseenCollectionData*> Collections;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Drop Data")
	TArray<FItemRarity> ExtraClothes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Drop Data")
	TArray<FItemRarity> ExtraAccessories;


	
};
