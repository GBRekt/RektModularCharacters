// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "JsonHandler.generated.h"

/**
 * 
 */
UCLASS()
class UNSEENMODULARCHARACTERS_API UJsonHandler : public UObject
{
	GENERATED_BODY()
public:
	void ExportCharMetaData(FUnseenCharacterMetaDataRef MetaDataRef, FUnseenCharacterMetaData MetaData,
					FPublicMetadata PublicMetaData, FString Path, int32 Counter);
	bool WriteJSONToFile(const FString& FilePath, const FUnseenCharacterMetaData& CharacterData);
	bool WriteJSONRefToFile(const FString& FilePath, const FUnseenCharacterMetaDataRef& CharacterData);
	void GeneratePublicMetadata(int Index,ECharGender Gender, FString StringPersonality);
	void GenerateStorePublicMetadata(int Index, FString Category, ERarity Rarity);
	void SerializePublicMetadata(const FString& FilePath, FPublicMetadata Metadata, int Index);
	bool WriteAssetJSONRefToFile(FString Path, const FString& FilePath, const FUnseenWearablesData& AssetData, EBodyPart BodyPart, EUnseenMaterialType MaterialType);
	void SerializeStorePublicMetadata(const FString& FilePath, FPublicMetadata Metadata, int Index);
	FUnseenCharacterMetaDataRef DeserializeJSON(FString JSONString);
	bool WriteColorPresetJSONRefToFile(FString FolderPath, const FString& FilePath, const FUnseenColorPreset& AssetData,
	                                   EBodyPart BodyPart);
	TArray<FString> ReadJsonFilesFromFolder();
};
