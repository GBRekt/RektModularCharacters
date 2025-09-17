// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "Engine/DataAsset.h"
#include "UnseenAssetData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UNSEENMODULARCHARACTERS_API UUnseenAssetData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, AssetRegistrySearchable ,meta = (ToolTip = "Item Display Name"), Category = "Properties")
	EBodyPart BodyPart = EBodyPart::BOD;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, AssetRegistrySearchable ,meta = (ToolTip = "Item Display Name"),Category = "Properties")
	FName AssetID = "";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, AssetRegistrySearchable ,meta = (ToolTip = "Item Display Name"), Category = "Properties")
	EUnseenMaterialType MaterialType = EUnseenMaterialType::Wearables;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, AssetRegistrySearchable ,meta = (ToolTip = "Item Display Name"), Category = "Properties")
	USkeletalMesh* GameMesh = nullptr;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, AssetRegistrySearchable ,meta = (ToolTip = "Item Display Name"), Category = "Properties")
	USkeletalMesh* SocialMediaMesh = nullptr;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, AssetRegistrySearchable ,meta = (ToolTip = "Item Display Name"), Category = "Properties")
	UTexture* Texture = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AssetRegistrySearchable ,meta = (ToolTip = "Item Display Name"), Category = "Unseen Character")
	bool bIsBodyTypeTexture;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, AssetRegistrySearchable ,meta = (ToolTip = "Item Display Name"), Category = "Properties")
	TArray<FUnseenCharacterColorLinear> Colors;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, AssetRegistrySearchable ,meta = (ToolTip = "Item Display Name"), Category = "Properties")
	TArray<FUnseenCharacterMaterialData> MaterialValues;
};
