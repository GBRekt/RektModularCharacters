// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePassData.h"

#include "UnseenAssetData.h"
#include "UnseenCollectionData.h"

TArray<FItemRarity> UBattlePassData::CollectSetAssetsFromCollections()
{
	TArray<FItemRarity> Assets;

	TArray<FItemRarity> FreeSets = CollectSetAssetsFromSingleCollection(FreeCollections);
	TArray<FItemRarity> PaidSets = CollectSetAssetsFromSingleCollection(PaidCollections);
	TArray<FItemRarity> GenerateSets = CollectSetAssetsFromSingleCollection(GeneratesCollections);
	TArray<FItemRarity> TopSets = CollectSetAssetsFromSingleCollection(TopCollections);

	Assets.Append(FreeSets);
	Assets.Append(PaidSets);
	Assets.Append(GenerateSets);
	Assets.Append(TopSets);

	UE_LOG(LogTemp, Error, TEXT("Found %d Assets"),Assets.Num());
	
	return Assets;
}

TArray<FItemRarity> UBattlePassData::CollectSetAssetsFromSingleCollection(TArray<FCollectionRarity> Collections)
{
	TArray<FItemRarity> ItemRarities;
	for(FCollectionRarity Collection : Collections)
	{
		TArray<UUnseenAssetData*> Assets = Collection.Asset->FilterClothesOnly();

		for(UUnseenAssetData* Asset : Assets)
		{
			//ItemRarities.Add(FItemRarity(Asset, Collection.Rarities));
		}
	}
	return ItemRarities;
}

TArray<UUnseenAssetData*> UBattlePassData::GatherChetItems(TArray<FChests> Chests)
{
	TArray<UUnseenAssetData*>  Assets;

	for(FChests Chest : Chests)
	{
		Assets.Append(Chest.ChestItems);
	}

	return Assets;
}

TArray<UUnseenAssetData*> UBattlePassData::CollectAccessories()
{
	TArray<UUnseenAssetData*> AccessoriesCollected;

	AccessoriesCollected.Append(GatherChetItems(FreeChests));
	AccessoriesCollected.Append(GatherChetItems(PaidChests));
	AccessoriesCollected.Append(GatherChetItems(GenerateChests));

	return AccessoriesCollected;	
}
