// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameTypes.h"
#include "UnseenColorPresetData.h"
#include "EditorDefaults.generated.h"

class UUnseenSocialMediaCharData;

/**
 * 
 */
UCLASS(Blueprintable)
class UNSEENMODULARCHARACTERS_API UEditorDefaults : public UDataAsset
{
	GENERATED_BODY()

public:
	
	// Convenience Maps //
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Look up Maps")
	TMap<EBodyPart, FString> BodyPartNamesMap;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Look up Maps")
	TMap<EPersonalities, FString> PersonalityNamesMap;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Look up Maps")
	TMap<EBodyType, FName> MaleBodyMorphTargetNames;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Look up Maps")
	TMap<EBodyType, FName> FemaleBodyMorphTargetNames;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Look up Maps")
	TMap<EPersonalities, FName> PersonalityMorphTargetNames;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Look up Maps")
	TArray<ECharGender> PermutationGenders;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Look up Maps")
	TArray<EBodyType> PermutationBodyTypes;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Look up Maps")
	TMap<int32, EPersonalities> IndexToPersonalityMap;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Look up Maps")
	TMap<EPersonalities, UUnseenSocialMediaCharData*> SocialMediaDataMap;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Look up Maps")
	TMap<EBodyPart, FString> BodyPartCategories;
	// Assets Data //
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	TMap<EBodyPart, UDataTable*> BodyPartAssetInfoTables;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	TMap<EBodyPart, UDataTable*> ColorArrayTables;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	TMap<ECharGender, UDataTable*> GenderFaceTables;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	TMap<ECharGender, UDataTable*> GenderBodyTables;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	UDataTable* HairColorPresets;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	UDataTable* EyeColorPresets;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	UDataTable* SkinTones;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	UDataTable* Collections;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	TMap<ECharGender, USkeletalMesh*> DefaultHair;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	TMap<EBodyPart, UDataTable*> DefaultWearableColorPresets;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	USkeletalMesh* DefaultBodyMesh;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	USkeletalMesh* DefaultRobotMesh;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	TArray<UUnseenAssetData*> UnderwearMale;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Data Management")
	TArray<UUnseenAssetData*> UnderwearFemale;

	//PDA ASSET DATA //
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Primary Data Assets")
	TMap<EBodyPart, UDataTable*> BodyPartPDATablesMale;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Primary Data Assets")
	TMap<EBodyPart, UDataTable*> BodyPartPDATablesFemale;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Primary Data Assets")
	TMap<EBodyPart, UDataTable*> ColorPDATables;
	


	// Materials //
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Materials")
	UMaterial* SkinMaterial;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Materials")
	UMaterial* SkinMaterialSM;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Materials")
	UMaterial* WearableMaterial;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Materials")
	UMaterial* FacialFeaturesMaterial;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Materials")
	UMaterial* RobotMaterial;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Materials")
	UMaterial* SocialMediaSkinMaterial;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Materials")
	UTexture* WhiteTexture;

	// Permutations Info //
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Permutations")
	FString BasePath;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Permutations")
	FString PermutationsPath;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Permutations")
	FString MetadataPath;
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Permutations")
	int PermutationsSeed;
	
	
	// Table Row Getters //
	UFUNCTION(BlueprintCallable, Category = "Data Getters")
	FUnseenWearablesDataRef GetAssetInfoFromTableByRowName(EBodyPart BodyPart, FName RowName);
	UFUNCTION(BlueprintCallable, Category = "Data Getters")
	FUnseenWearablesDataRef GetAssetInfoFromTableByIndex(EBodyPart BodyPart, int32 Index);
	UFUNCTION(BlueprintCallable, Category = "Data Getters")
	FDataLookup GetAssetPdaFromTableByIndex(EBodyPart BodyPart, int32 Index, ECharGender Gender);
	UFUNCTION(BlueprintCallable, Category = "Data Getters")
	FDataLookup GetColorPdaFromTableByIndex(EBodyPart BodyPart, int32 Index);
	UFUNCTION(BlueprintCallable, Category = "Data Getters")
	FName GetAssetInfoRowName(EBodyPart BodyPart, int32 Index);
	UFUNCTION(BlueprintCallable, Category = "Data Getters")
	FUnseenColorPresetLinear GetColorFromTableByIndex(EBodyPart BodyPart, int32 Index);

	
	UFUNCTION(BlueprintCallable, Category = "Conversions")
	FName GetPersonalityMorphTarget(ECharGender Gender, EPersonalities Personality);
	FName GetBodyTypeMorphTarget(ECharGender Gender, EBodyType BodyType);
	FUnseenWearablesDataRef GetFaceDataRow(ECharGender Gender, EPersonalities Personality);
	FUnseenWearablesDataRef GetBodyDataRow(ECharGender Gender, EBodyType BodyType, bool IsRobot);
	FUnseenCollectionInfo GetCollectionInfoByIndex(int32 Index);
	int32 GetAssetInfoRowIndex(EBodyPart BodyPart, FName RowName);
	TMap<EBodyPart, FUnseenColorPresetLinear> GetDefaultColorPreset();
	FUnseenColorPresetLinear GetDefaultWearableColorPreset(EBodyPart BodyPart, int32 Index);


	UFUNCTION(BlueprintCallable, Category = "Conversions")
	FUnseenCharacterColor ConvertUnseenColorToInt (FUnseenCharacterColorLinear LinearColor);
	UFUNCTION(BlueprintCallable, Category = "Conversions")
	FUnseenCharacterColorLinear ConvertUnseenColorToLinear (FUnseenCharacterColor IntColor);
	UFUNCTION(BlueprintCallable, Category = "Conversions")
	FName FormatNftIdInfo(const FNftIdInfo& NftInfo);
	UFUNCTION(BlueprintCallable, Category = "Conversions")
	FUnseenCharacterGlobalData ConvertGlobalDataRefToData(FUnseenCharacterGlobalDataRef GlobalDataRef, bool IsRobot);
	UFUNCTION(BlueprintCallable, Category = "Conversions")
	FString ConvertBodyTypeToString(EBodyType BodyType, ECharGender Gender);
	FString ConvertPersonalityToString(EPersonalities Personality, ECharGender Gender);
	UFUNCTION(BlueprintCallable, Category = "Conversions")
	FUnseenCharacterTexture ConvertCharacterTextureRefToData(FUnseenCharacterTextureRef CharTextureRef);
	UFUNCTION(BlueprintCallable, Category = "Conversions")
	FUnseenCharacterMetaData ConvertCharacterRefToData(FUnseenCharacterMetaDataRef CharacterMetaDataRef, bool IsRobot);
	UFUNCTION(BlueprintCallable, Category = "Conversions")
	FUnseenCharacterMetaDataRef CollectMetaDataRef(FUnseenCharacterGlobalDataRef GlobalDataRef, TMap<EBodyPart,
		FUnseenWearablesDataRef> CurrentAssetsInfo);
	UFUNCTION(BlueprintCallable, Category = "Conversions")
	FUnseenWearablesData ConvertAssetInfoRefToData(FUnseenWearablesDataRef AssetInfo);
	FPublicMetadata GeneratePublicMetaData(FPublicMetadata Metadata, int32 Index, FUnseenPresetGlobalData GlobalData, bool bIsFreemium);
	TArray<FUnseenCharacterColorLinear> ConvertPresetToColorArray(FUnseenColorPresetLinear ColorPreset);
	UDataTable* GetDataTableFromPDA(EBodyPart BodyPart, bool bIsAssetInfo, ECharGender Gender);
	TArray<FName> GetRowNames(const EBodyPart BodyPart, ECharGender Gender);
	TArray<FName> GetColorArrayRowNames(const EBodyPart BodyPart);
	TArray<FName> GetFaceRowNames(ECharGender Gender);
	TArray<FName> GetSkinToneRowNames();
	EPersonalities IndexToPersonality(int32 Index);
	FUnseenColorPreset ConvertColorPresetLinearToInt(FUnseenColorPresetLinear PresetLinear);
	FUnseenWearablesDataRef GetAndConvertPdaToDataRefFromIndex(EBodyPart BodyPart, int32 AssetIndex, int32 ColorIndex, ECharGender Gender);
	FUnseenWearablesDataRef ConvertPdaToWearableDataRef(UUnseenAssetData* AssetPda, UUnseenColorPresetData* ColorPda,
	                                                    int32 ColorIndex);
	TArray<FUnseenWearablesDataRef> GetAndConvertCollectionToDataRefFromIndex(FName RowName);
	FPublicMetadata GenerateStorePublicMetadata(int Index, FString Category, ERarity Rarity);
};
