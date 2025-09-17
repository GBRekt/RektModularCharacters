// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameTypes.h"
#include "UnseenCharacter.h"
#include "CharacterDataOperations.generated.h"

class UEditorDefaults;

/**
 * 
 */
UCLASS(Blueprintable)
class UNSEENPLUGINSMASTER_API UCharacterDataOperations : public UObject
{
	GENERATED_BODY()
public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "References")
	UEditorDefaults* EditorDefaults;


	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void ExportAllCollections();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void ExportCollection(FString Path, FUnseenCollectionInfo CollectionInfo, int32 StartingIndex);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void ExportAssetJSON(FString Path, int index, FUnseenWearablesDataRef AssetInfo, EUnseenMaterialType MaterialType);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void GeneratePermutations(FPublicMetadata Metadata, int32 CategoryResultCount, FString Path);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void ExportColorPresets(FString Path, EBodyPart BodyPartOperation);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void ExportBattlePass(UBattlePassData* BattlePass, FString Path);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void ExportCurrentCharacter(FPublicMetadata Metadata, AUnseenCharacter* Character, FString Path, int32 Index, bool bIsFreemium);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void ExportStoreItems(TArray<FItemRarity> StoreItems, FString Path);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void ExportCustomizableJSONByBodyPart(FString Path, EBodyPart BodyPart);



	// Helper Methods //
	UFUNCTION(Category = "Helpers")
	FUnseenCharacterMetaDataRef ConvertIndicesToPda(FPermutationIndices CharacterIndices);
	UFUNCTION(Category = "Helpers")
	TArray<FPermutationIndices> SplitShuffleChopResults(TArray<FPermutationIndices> Permutations, int32 CategoryResultCount);
	UFUNCTION(Category = "Helpers")
	TArray<FUnseenWearablesDataRef> GenerateDefaultsPda(int32 ColorIndex);
	TArray<FUnseenWearablesDataRef> GenerateUnderwear(FUnseenCharacterMetaDataRef Character);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "External Tools")
	void LaunchPhotoshop();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "External Tools")
	void RunTexturePipeline();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Asset Validation")
	FString ValidateAssetsFromDataTables(
	const TMap<EBodyPart, UDataTable*>& DataTableMap,
	const FString& RootPath,
	bool LogFound,
	bool LogMissing,
	FString Name);
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "External Tools")
	void OpenFolderInExplorer(const FString& FolderPath);
	
};
