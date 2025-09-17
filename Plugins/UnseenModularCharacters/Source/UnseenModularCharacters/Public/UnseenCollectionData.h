// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameTypes.h"
#include "UnseenCollectionData.generated.h"

class UUnseenAssetData;

/**
 * 
 */
UCLASS(Blueprintable)
class UNSEENMODULARCHARACTERS_API UUnseenCollectionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	TMap<EBodyPart, UUnseenAssetData*> Nfts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	int StartingID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	bool Released = false;    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FName BodyMorphTarget = "BODSM";

	UFUNCTION(BlueprintCallable, Category = "JSONS Operations")
	TArray<UUnseenAssetData*> FilterClothesOnly();
	
};
