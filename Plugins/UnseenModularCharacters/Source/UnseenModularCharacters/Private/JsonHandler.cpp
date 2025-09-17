// Fill out your copyright notice in the Description page of Project Settings.
#include "JsonHandler.h"
#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "GameTypes.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"



//TO DO:
// Add export color presets

void UJsonHandler::ExportCharMetaData(FUnseenCharacterMetaDataRef MetaDataRef, FUnseenCharacterMetaData MetaData,
					FPublicMetadata PublicMetaData, FString Path, int32 Counter)
{
	WriteJSONToFile(*FString::Printf(TEXT("%s/private/%d"), *Path, Counter), MetaData);
	WriteJSONRefToFile(*FString::Printf(TEXT("%s/RenderRef/%d.json"), *Path, Counter), MetaDataRef);
	SerializePublicMetadata(*FString::Printf(TEXT("%s/json/%d"), *Path, Counter), PublicMetaData, Counter);
}

bool UJsonHandler::WriteJSONToFile(const FString& FilePath, const FUnseenCharacterMetaData& CharacterData)
{
	FString JSONString;
	FJsonObjectConverter::UStructToJsonObjectString(CharacterData, JSONString, 0, 0);
	FString FullFilePath = FPaths::ProjectDir() + FilePath;
	FString Directory = FPaths::GetPath(FullFilePath);
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*Directory))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*Directory);
	}
	return FFileHelper::SaveStringToFile(JSONString, *FullFilePath);
}

bool UJsonHandler::WriteJSONRefToFile(const FString& FilePath, const FUnseenCharacterMetaDataRef& CharacterData)
{
	FString JSONString;
	FJsonObjectConverter::UStructToJsonObjectString(CharacterData, JSONString, 0, 0);
	FString FullFilePath = FPaths::ProjectDir() + FilePath;
	FString Directory = FPaths::GetPath(FullFilePath);
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*Directory))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*Directory);
	}
	return FFileHelper::SaveStringToFile(JSONString, *FullFilePath);
}

void UJsonHandler::GeneratePublicMetadata(int Index,ECharGender Gender, FString StringPersonality)
{
	FPublicMetadata Metadata;
	Metadata.Name = "The Generates #" + FString::FromInt(Index);
	Metadata.Image = "https://dev.assets.playunseen.com/thegenerates/assets/images/" + FString::FromInt(Index) + ".jpg";
	Metadata.Season = 1;
	Metadata.Attributes.Add(FPublicMetadataAttributes(
		"Level", "1"));
	Metadata.Attributes.Add(FPublicMetadataAttributes("Gender", UEnum::GetDisplayValueAsText(Gender).ToString()));

	
	Metadata.Attributes.Add(FPublicMetadataAttributes("Personality", StringPersonality));
}

void UJsonHandler::GenerateStorePublicMetadata(int Index,FString Category, ERarity Rarity)
{
	FPublicMetadata Metadata;
	Metadata.Name = "Unseen Store #" + FString::FromInt(Index);
	Metadata.Image = "https://dev.assets.playunseen.com/unseenstore/assets/images/" + FString::FromInt(Index) + ".jpg";
	Metadata.Description = "A captivating selection of rare in-game assets and apparel, designed to elevate your digital adventures with style and exclusivity.";
	Metadata.Season = 1;
	Metadata.Attributes.Add(FPublicMetadataAttributes(
		"Category", Category));
	Metadata.Attributes.Add(FPublicMetadataAttributes("Item Type", "FilteringCategoryToBeDetermined"));
	Metadata.Attributes.Add(FPublicMetadataAttributes("Rarity", UEnum::GetValueAsName(Rarity).ToString()));
}


void UJsonHandler::SerializePublicMetadata(const FString& FilePath, FPublicMetadata Metadata, int Index)
{
	FString MetadataString;
	FJsonObjectConverter::UStructToJsonObjectString(Metadata, MetadataString, 0, 0);
	FString FullFilePath = FPaths::ProjectDir() + FilePath;
	FString Directory = FPaths::GetPath(FullFilePath);
	// Ensure the original directory exists
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*Directory))
	{
		if (!FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*Directory))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create directory: %s"), *Directory);
			return;
		}
	}
	// Save to original location
	if (FFileHelper::SaveStringToFile(MetadataString, *FullFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully saved to: %s"), *FullFilePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save file to: %s"), *FullFilePath);
		return;
	}
}

bool UJsonHandler::WriteAssetJSONRefToFile(FString Path, const FString& FilePath, const FUnseenWearablesData& AssetData, EBodyPart BodyPart, EUnseenMaterialType MaterialType)
{
	FString JSONString;
	FJsonObjectConverter::UStructToJsonObjectString(AssetData, JSONString, 0, 0);
	FString FullFilePath;

	switch(MaterialType)
	{
	case EUnseenMaterialType::Wearables:
	case EUnseenMaterialType::Custom:
		FullFilePath = FPaths::ProjectDir() + Path + "/private/" + FilePath;
		break;
	case EUnseenMaterialType::FacialFeatures:
		FullFilePath = FPaths::ProjectDir() + "NFT/customizables/" + UEnum::GetDisplayValueAsText(BodyPart).ToString() + "/" + FilePath;
		break;
	default:
		break;
	}
	FString Directory = FPaths::GetPath(FullFilePath);

	// Ensure directory exists, or create it
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*Directory))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*Directory);
	}

	// Write JSON to file
	return FFileHelper::SaveStringToFile(JSONString, *FullFilePath);
}

void UJsonHandler::SerializeStorePublicMetadata(const FString& FilePath, FPublicMetadata Metadata, int Index)
{
	FString MetadataString;
	FJsonObjectConverter::UStructToJsonObjectString(Metadata, MetadataString, 0, 0);
	FString FullFilePath = FPaths::ProjectDir() + FilePath;
	FString Directory = FPaths::GetPath(FullFilePath);
	// Ensure the original directory exists
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*Directory))
	{
		if (!FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*Directory))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create directory: %s"), *Directory);
			return;
		}
	}
	// Save to original location
	if (FFileHelper::SaveStringToFile(MetadataString, *FullFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully saved to: %s"), *FullFilePath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save file to: %s"), *FullFilePath);
		return;
	}
}

TArray<FString> UJsonHandler::ReadJsonFilesFromFolder()
{
	TArray<FString> JsonFileContents;
	FString ReadFolderPath = FPaths::ProjectDir() + "Permutations/RenderRef";
	TArray<FString> JsonFiles;
	IFileManager& FileManager = IFileManager::Get();
	FileManager.FindFiles(JsonFiles, *ReadFolderPath, TEXT("*.json"));
	JsonFiles.Sort([](const FString& A, const FString& B) {
		return FCString::Atoi(*A) < FCString::Atoi(*B);
	});
	JsonFileContents.Empty();
	for (const FString& FileName : JsonFiles)
	{
		FString FilePath = FPaths::Combine(ReadFolderPath, FileName);
		FString FileContent;

		if (FFileHelper::LoadFileToString(FileContent, *FilePath))
		{
			JsonFileContents.Add(FileContent);
			UE_LOG(LogTemp, Warning, TEXT("Loaded JSON file: %s"), *FileName);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to read JSON file: %s"), *FileName);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Successfully loaded %d JSON files."), JsonFileContents.Num());
	return JsonFiles;
}

FUnseenCharacterMetaDataRef UJsonHandler::DeserializeJSON(FString JSONString)
{
	FUnseenCharacterMetaDataRef JSONObject;
	FJsonObjectConverter::JsonObjectStringToUStruct(JSONString, &JSONObject ,0,0 );	
	return JSONObject;
}

bool UJsonHandler::WriteColorPresetJSONRefToFile(FString FolderPath, const FString& FilePath, const FUnseenColorPreset& AssetData, EBodyPart BodyPart)
{
	FString JSONString;
	FJsonObjectConverter::UStructToJsonObjectString(AssetData, JSONString, 0, 0);
	FString FullFilePath = FPaths::ProjectDir() + FolderPath+ "/" + UEnum::GetDisplayValueAsText(BodyPart).ToString() + "/" + FilePath;
	FString Directory = FPaths::GetPath(FullFilePath);

	// Ensure directory exists, or create it
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*Directory))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*Directory);
	}

	// Write JSON to file
	return FFileHelper::SaveStringToFile(JSONString, *FullFilePath);
}
