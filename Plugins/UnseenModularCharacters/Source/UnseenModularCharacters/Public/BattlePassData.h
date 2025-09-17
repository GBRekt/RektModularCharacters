// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameTypes.h"
#include "BattlePassData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UNSEENMODULARCHARACTERS_API UBattlePassData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FDateTime ReleaseData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FCollectionRarity> FreeCollections;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FChests> FreeChests;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FCollectionRarity> PaidCollections;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FChests> PaidChests;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FCollectionRarity> GeneratesCollections;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FChests> GenerateChests;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FCollectionRarity> TopCollections;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<UUnseenAssetData*> Accessories;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int StartingId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Unseen Character Assets", meta=(MultiLine=true))
	FString Notes;

	UFUNCTION(BlueprintCallable, Category = "JSON Operations")
	TArray<FItemRarity> CollectSetAssetsFromCollections();
	UFUNCTION(BlueprintCallable, Category = "JSON Operations")
	TArray<FItemRarity> CollectSetAssetsFromSingleCollection(TArray<FCollectionRarity> Collections);
	UFUNCTION(BlueprintCallable, Category = "JSON Operations")
	TArray<UUnseenAssetData*> GatherChetItems(TArray<FChests> Chests);
	UFUNCTION(BlueprintCallable, Category = "JSON Operations")
	TArray<UUnseenAssetData*> CollectAccessories();
};
