// Fill out your copyright notice in the Description page of Project Settings.


#include "UnseenCollectionData.h"

#include "UnseenAssetData.h"

TArray<UUnseenAssetData*> UUnseenCollectionData::FilterClothesOnly()
{
	TArray<UUnseenAssetData*> Clothes;

	for(TPair<EBodyPart, UUnseenAssetData*> NftData : Nfts)
	{
		if(NftData.Key!= EBodyPart::AEY && NftData.Key!=EBodyPart::AHD)
		{
			Clothes.Add(NftData.Value);
			UE_LOG(LogTemp, Warning, TEXT("Added %s"), *NftData.Value->GetName());
		}
	}
	
	return Clothes;
}
