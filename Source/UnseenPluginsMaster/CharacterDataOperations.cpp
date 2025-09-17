// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDataOperations.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "AssetToolsModule.h"
#include "Factories/Factory.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "Framework/Application/SlateApplication.h"
#include "BattlePassData.h"
#include "EditorDefaults.h"
#include "UnseenAssetData.h"
#include "JsonHandler.h"

#include "UnseenCharacter.h"


template<typename T>
void ShuffleArray(TArray<T>& Array, int32 Seed)
{
	FRandomStream RandomStream(Seed); 

	for (int32 i = Array.Num() - 1; i > 0; i--)
	{
		int32 j = RandomStream.RandRange(0, i); 
		Array.Swap(i, j);
	}
}


void UCharacterDataOperations::ExportAllCollections()
{
	int32 IncrementalIndex = 1;
	for(int32 i = 0; i<EditorDefaults->Collections->GetRowNames().Num(); i++)
	{
		FUnseenCollectionInfo CollectionInfo = EditorDefaults->GetCollectionInfoByIndex(i);
		ExportCollection("", CollectionInfo, IncrementalIndex);
		IncrementalIndex += CollectionInfo.Nfts.Num();
	}
}

void UCharacterDataOperations::ExportCollection(FString Path, FUnseenCollectionInfo CollectionInfo, int32 StartingIndex)
{
	UJsonHandler* JsonHandler = NewObject<UJsonHandler>();
	TArray<FName> RowNames = EditorDefaults->Collections->GetRowNames();
	if(RowNames.IsValidIndex(0))
	{
		for(int32 i  = 0; i<CollectionInfo.Nfts.Num(); i++)
		{
			FNftIdInfo Nft = CollectionInfo.Nfts[i]; 
			FName RowName = EditorDefaults->FormatNftIdInfo(Nft);
			FUnseenWearablesDataRef AssetInfo = EditorDefaults->GetAssetInfoFromTableByRowName(Nft.BodyPart, RowName);			
			ExportAssetJSON(Path, StartingIndex + i, AssetInfo, EUnseenMaterialType::Wearables );
		}
	}

}

void UCharacterDataOperations::ExportAssetJSON(FString Path, int index, FUnseenWearablesDataRef AssetInfo, EUnseenMaterialType MaterialType)
{
	FUnseenWearablesData CharacterString = EditorDefaults->ConvertAssetInfoRefToData(AssetInfo);
	CharacterString.wearable_id = FString::FromInt(index);
	UJsonHandler* JsonHandler = NewObject<UJsonHandler>();
	JsonHandler->WriteAssetJSONRefToFile(Path, FString::Printf(TEXT("%d"), index), CharacterString, AssetInfo.bodyPart, MaterialType);
}

void UCharacterDataOperations::GeneratePermutations(FPublicMetadata Metadata, int32 CategoryResultCount, FString Path)
{
	
	FRandomStream PermSeed;
	PermSeed.Initialize(EditorDefaults->PermutationsSeed);
	
	UJsonHandler* JsonHandler = NewObject<UJsonHandler>();
	if(!EditorDefaults)
	{
		UE_LOG(LogTemp, Error, TEXT("Editor Defaults PDA was not found."));
		return;
	}

	int Counter = 0;
	FPermutationIndices CharPermutationIndices;
	TArray<FPermutationIndices> Permutations;
	
	// Permute Genders
	for(int GenderIndex = 0; GenderIndex < EditorDefaults->PermutationGenders.Num(); GenderIndex++)
	{
		ECharGender PermutationGender = (GenderIndex == 0)? ECharGender::Male : ECharGender::Female; 
	    CharPermutationIndices.Gender = GenderIndex;

	    // Permute Body Types
	    for(int BodyTypeIndex = 0; BodyTypeIndex < 3; BodyTypeIndex++)
	    {
	        CharPermutationIndices.BodyType = BodyTypeIndex;

	        // Permute Personalities
	        for(int PersonalityIndex = 0; PersonalityIndex < EditorDefaults->GetFaceRowNames(ECharGender::Male).Num(); PersonalityIndex++)
	        {
	            CharPermutationIndices.Personality = PersonalityIndex;

	            // Permute Skin Tones
	            for(int SkinToneIndex = 0; SkinToneIndex < EditorDefaults->GetSkinToneRowNames().Num(); SkinToneIndex++)
	            {
	                CharPermutationIndices.SkinTone = SkinToneIndex;

	                // Permute Hair Colors
	                for(int HairColorIndex = 0; HairColorIndex < EditorDefaults->GetColorArrayRowNames(EBodyPart::HAI).Num(); HairColorIndex++)
	                {
	                    CharPermutationIndices.HairColor = HairColorIndex;

	                    // Permute Hairstyles
	                    for(int HairIndex = 0; HairIndex < EditorDefaults->GetRowNames(EBodyPart::HAI, PermutationGender).Num(); HairIndex++)
	                    {
	                        CharPermutationIndices.Hair = HairIndex;

	                        // Assign random Onesie Color
	                        int OnesieColorIndex = PermSeed.RandRange(0, EditorDefaults->GetColorArrayRowNames(EBodyPart::CLU).Num() - 1);
	                        CharPermutationIndices.OnesieColor = OnesieColorIndex;

	                        // Assign random Shoe Color
	                        int ShoeColorIndex = PermSeed.RandRange(0, EditorDefaults->GetColorArrayRowNames(EBodyPart::SHO).Num() - 1);
	                        CharPermutationIndices.ShoeColor = ShoeColorIndex;

	                        // Assign random Eyebrow
	                        int EyebrowsIndex = PermSeed.RandRange(0, EditorDefaults->GetRowNames(EBodyPart::EYB, PermutationGender).Num() - 1);
	                        CharPermutationIndices.Eyebrows = EyebrowsIndex;

	                        // Assign default Eye value and random Eye Color
	                        CharPermutationIndices.Eyes = 0;
	                        int EyeColorIndex = PermSeed.RandRange(0, EditorDefaults->GetColorArrayRowNames(EBodyPart::EYE).Num() - 1);
	                        CharPermutationIndices.EyeColor = EyeColorIndex;

	                        // If male, assign random Facial Hair
	                        if (GenderIndex == 0)
	                        {
	                        	float RandomValue = PermSeed.FRandRange(0.f, 1.f);
	                        	if(RandomValue>0.2)
	                        	{
	                        		int FacialHairIndex = PermSeed.RandRange(0, EditorDefaults->GetRowNames(EBodyPart::FAH, PermutationGender).Num() - 1);
	                        		CharPermutationIndices.FacialHair = FacialHairIndex;
	                        	}
	                        }

	                        // Counter for keeping track of permutations
                    		Permutations.Add(CharPermutationIndices);
	                    }
	                }
	            }
	        }
	    }
	}
	TArray<FPermutationIndices> SelectedPermutations = SplitShuffleChopResults(Permutations, CategoryResultCount);
	for(FPermutationIndices Permutation : SelectedPermutations)
	{
		//Character JSONs
		Counter++;
		FUnseenCharacterMetaDataRef CharacterMetaDataRef = ConvertIndicesToPda(Permutation);
		FUnseenCharacterMetaData CharacterMetaData = EditorDefaults->ConvertCharacterRefToData(CharacterMetaDataRef, false);
		FUnseenPresetGlobalData PermutationGlobalData;
		PermutationGlobalData.gender = CharacterMetaDataRef.globalData.gender;
		PermutationGlobalData.personality = CharacterMetaDataRef.globalData.personality;
		FPublicMetadata CharacterPublicMetadata = EditorDefaults->GeneratePublicMetaData(Metadata, Counter, PermutationGlobalData, false);
		JsonHandler->ExportCharMetaData(CharacterMetaDataRef, CharacterMetaData, CharacterPublicMetadata, Path, Counter);
	}
}

FUnseenCharacterMetaDataRef UCharacterDataOperations::ConvertIndicesToPda(FPermutationIndices CharacterIndices)
{
	FUnseenCharacterMetaDataRef Character;

	
	Character.globalData.gender = EditorDefaults->PermutationGenders[CharacterIndices.Gender];
	Character.globalData.bodyType = EditorDefaults->PermutationBodyTypes[CharacterIndices.BodyType];
	Character.globalData.skinTone = EditorDefaults->GetColorFromTableByIndex(EBodyPart::BOD, CharacterIndices.SkinTone).PresetColors[0].Color;
	Character.globalData.bodyMesh = EditorDefaults->DefaultBodyMesh;
	
	FUnseenCharacterTextureRef FaceTextureInfo;
	FaceTextureInfo.name = "FAC";
	FaceTextureInfo.paramName = "Main";
	
	FUnseenCharacterTextureRef BodyTextureInfo;
	BodyTextureInfo.name = "BOD";
	BodyTextureInfo.paramName = "Main";
	
	Character.globalData.personality = EditorDefaults->IndexToPersonality(CharacterIndices.Personality);
	FUnseenWearablesDataRef Face = EditorDefaults->GetFaceDataRow(Character.globalData.gender , Character.globalData.personality);
	FUnseenWearablesDataRef Body = EditorDefaults->GetBodyDataRow(Character.globalData.gender , Character.globalData.bodyType, false);
	
	BodyTextureInfo.texture = Body.texture;
	FaceTextureInfo.texture = Face.texture;
	Character.globalData.textures.Add(FaceTextureInfo);
	Character.globalData.textures.Add(BodyTextureInfo);

	// Adding Hair Customizable //
	Character.customizableData.Add( EditorDefaults->GetAndConvertPdaToDataRefFromIndex(EBodyPart::HAI,
																				CharacterIndices.Hair,
																				CharacterIndices.HairColor,
																				Character.globalData.gender));

	UE_LOG(LogTemp, Log, TEXT("Customizable Length %d"), Character.customizableData.Num());
	// Adding Eyebrows Customizable //
	Character.customizableData.Add( EditorDefaults->GetAndConvertPdaToDataRefFromIndex(EBodyPart::EYB,
																			CharacterIndices.Eyebrows,
																			CharacterIndices.HairColor,
																			Character.globalData.gender));
	// Adding Eyes Customizable //
	Character.customizableData.Add( EditorDefaults->GetAndConvertPdaToDataRefFromIndex(EBodyPart::EYE,
																		CharacterIndices.Eyes,
																		CharacterIndices.EyeColor,
																		Character.globalData.gender));
	if(Character.globalData.gender == ECharGender::Male)
	{
		// Adding Facial Hair Customizable //
		Character.customizableData.Add( EditorDefaults->GetAndConvertPdaToDataRefFromIndex(EBodyPart::FAH,
																		CharacterIndices.FacialHair,
																		CharacterIndices.HairColor,
																		Character.globalData.gender));
	}
	
	Character.default_wearables = GenerateDefaultsPda(CharacterIndices.OnesieColor);
	Character.wearables = Character.default_wearables;
	Character.underwear = GenerateUnderwear(Character);

	return Character;
}

TArray<FUnseenWearablesDataRef> UCharacterDataOperations::GenerateDefaultsPda(int32 ColorIndex)
{
	TArray<FUnseenWearablesDataRef> DefaultWearables;
	DefaultWearables.Add( EditorDefaults->GetAndConvertPdaToDataRefFromIndex(EBodyPart::CLU,0, ColorIndex, ECharGender::Male));
	DefaultWearables.Add( EditorDefaults->GetAndConvertPdaToDataRefFromIndex(EBodyPart::CLL,0, ColorIndex, ECharGender::Male));
	DefaultWearables.Add( EditorDefaults->GetAndConvertPdaToDataRefFromIndex(EBodyPart::SHO,0, ColorIndex, ECharGender::Male));
	
	return DefaultWearables;
}
TArray<FUnseenWearablesDataRef> UCharacterDataOperations::GenerateUnderwear(FUnseenCharacterMetaDataRef Character)
{
	TArray<FUnseenWearablesDataRef> UnderwearList;
	if(Character.globalData.gender == ECharGender::Male)
	{
		for(int32 i = 0; i<EditorDefaults->UnderwearMale.Num(); i++)
		{
			UUnseenAssetData* Underwear = EditorDefaults->UnderwearMale[i];
			UnderwearList.Add(EditorDefaults->ConvertPdaToWearableDataRef(Underwear, nullptr, -1));
		}
	}
	else
	{
		for(int32 i = 0; i<EditorDefaults->UnderwearFemale.Num(); i++)
		{
			UUnseenAssetData* Underwear = EditorDefaults->UnderwearFemale[i];
			UnderwearList.Add(EditorDefaults->ConvertPdaToWearableDataRef(Underwear, nullptr, -1));
		}
	}

	return UnderwearList;
}

void UCharacterDataOperations::LaunchPhotoshop()
{
	// Replace with the actual path to Photoshop on your machine
	const FString PhotoshopExe = TEXT("C:/Program Files/Adobe/Adobe Photoshop 2024/Photoshop.exe");

	if (!FPaths::FileExists(PhotoshopExe))
	{
		UE_LOG(LogTemp, Error, TEXT("Photoshop executable not found at: %s"), *PhotoshopExe);
		return;
	}

	FProcHandle ProcHandle = FPlatformProcess::CreateProc(
		*PhotoshopExe,
		nullptr,           // No command-line args needed to just launch
		true,              // bLaunchDetached
		false,             // bLaunchHidden
		false,             // bLaunchReallyHidden
		nullptr,           // OutProcessID
		0,                 // Priority
		NULL,              // Optional working directory
		NULL               // Pipe handles (not needed)
	);

	if (ProcHandle.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Launched Photoshop successfully."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to launch Photoshop."));
	}
}
TArray<FPermutationIndices> UCharacterDataOperations::SplitShuffleChopResults(TArray<FPermutationIndices> Permutations, int32 CategoryResultCount)
{
	int TotalGroups = 36;
	int GroupSize = Permutations.Num() / TotalGroups;
	TArray<FPermutationIndices> GroupArray;
	TArray<FPermutationIndices> ResultsArray;
	for (int i = 0; i < TotalGroups; i++)
	{
		GroupArray.Empty();		
		int32 StartIndex = i * GroupSize;
		if (StartIndex + GroupSize <= Permutations.Num())
		{
			GroupArray.Append(&Permutations[StartIndex], GroupSize);
		}		 
		ShuffleArray(GroupArray, EditorDefaults->PermutationsSeed+i);
		if (GroupArray.Num() > CategoryResultCount)
		{
			GroupArray.SetNum(CategoryResultCount);
		}
		ResultsArray.Append(GroupArray);
	}
	ShuffleArray(ResultsArray, EditorDefaults->PermutationsSeed);
	return ResultsArray;
}

void UCharacterDataOperations::ExportColorPresets(FString Path,EBodyPart BodyPartOperation)
{
	UJsonHandler* JsonHandler = NewObject<UJsonHandler>();
	if(!EditorDefaults->ColorPDATables.Contains(BodyPartOperation))
	{
		return;
	}
	UDataTable* DataTable = *EditorDefaults->ColorPDATables.Find(BodyPartOperation);
	TArray<FName> RowNames = DataTable->GetRowNames();
	for(int32 i = 0; i<RowNames.Num(); i++)
	{
		UUnseenColorPresetData* RowData = Cast<UUnseenColorPresetData>(DataTable->FindRow<FDataLookup>(RowNames[i], TEXT("Lookup Color Presets"))->DataAsset);
		if (RowData)
		{
			FUnseenColorPreset Preset = EditorDefaults->ConvertColorPresetLinearToInt(FUnseenColorPresetLinear(RowData->PresetIndex, RowData->IconColors, RowData->PresetColors));
			JsonHandler->WriteColorPresetJSONRefToFile(Path, FString::Printf(TEXT("%d"), i+1), Preset, BodyPartOperation);
		}
	}
}

void UCharacterDataOperations::ExportBattlePass(UBattlePassData* BattlePass, FString Path)
{
		if(!BattlePass)
	{
		return;
	}

	TArray<FItemRarity> BattlePassAssets = BattlePass->CollectSetAssetsFromCollections();
	TArray<UUnseenAssetData*> Accessories = BattlePass->CollectAccessories();

	int Counter = BattlePass->StartingId;
	UJsonHandler* JsonHandler = NewObject<UJsonHandler>();
	
	for(FItemRarity Item : BattlePassAssets)
	{
		for (ERarity Rarity : Item.Rarities)
		{
			Counter++;
			FUnseenWearablesDataRef DataRef = EditorDefaults->ConvertPdaToWearableDataRef(Item.Asset, nullptr, 0);
			FUnseenWearablesData AssetData = EditorDefaults->ConvertAssetInfoRefToData(DataRef);
			AssetData.wearable_id = FString::FromInt(Counter);
			JsonHandler->WriteAssetJSONRefToFile(Path, FString::Printf(TEXT("%d"), Counter), AssetData, Item.Asset->BodyPart,Item.Asset->MaterialType);
			FString Category = "";

			if(EditorDefaults->BodyPartCategories.Contains(Item.Asset->BodyPart))
			{
				Category = *EditorDefaults->BodyPartCategories.Find(Item.Asset->BodyPart);
			}
			FPublicMetadata AssetPublicMetadata = EditorDefaults->GenerateStorePublicMetadata(Counter, Category, Rarity);
	
			JsonHandler->SerializeStorePublicMetadata(*FString::Printf(TEXT("%s/json/%d"), *Path, Counter), AssetPublicMetadata, Counter);

		}
	}
	for(UUnseenAssetData* Accessory : Accessories)
	{

			Counter++;
			FUnseenWearablesDataRef DataRef = EditorDefaults->ConvertPdaToWearableDataRef(Accessory, nullptr, 0);
			FUnseenWearablesData AssetData = EditorDefaults->ConvertAssetInfoRefToData(DataRef);
			AssetData.wearable_id = FString::FromInt(Counter);
			JsonHandler->WriteAssetJSONRefToFile(Path, FString::Printf(TEXT("%d"), Counter), AssetData, Accessory->BodyPart,Accessory->MaterialType);
			FString Category = "";

			if(EditorDefaults->BodyPartCategories.Contains(Accessory->BodyPart))
			{
				Category = *EditorDefaults->BodyPartCategories.Find(Accessory->BodyPart);
			}
			FPublicMetadata AssetPublicMetadata = EditorDefaults->GenerateStorePublicMetadata(Counter, Category, ERarity::None);
	
			JsonHandler->SerializeStorePublicMetadata(*FString::Printf(TEXT("%s/json/%d"), *Path, Counter), AssetPublicMetadata, Counter);

	}
}

void UCharacterDataOperations:: ExportCurrentCharacter(FPublicMetadata Metadata, AUnseenCharacter* Character, FString Path, int32 Index, bool bIsFreemium)
{	
	UJsonHandler* JsonHandler = NewObject<UJsonHandler>();
	FUnseenCharacterMetaDataRef CharacterMetaDataRef;
	
	TArray<FUnseenWearablesDataRef> Customizables;
	TArray<FUnseenWearablesDataRef> Wearables;
	for(TPair<EBodyPart, UUnseenAssetData*> AssetInfo : Character->CurrentCharacter)
	{
		switch(AssetInfo.Key)
		{
		case EBodyPart::HAI:
		case EBodyPart::EYB:	
		case EBodyPart::FAH:
			Customizables.Add(EditorDefaults->ConvertPdaToWearableDataRef(AssetInfo.Value, Character->Global.HairColorPreset, -1));
			break;
		case EBodyPart::EYE:
			Customizables.Add(EditorDefaults->ConvertPdaToWearableDataRef(AssetInfo.Value, Character->Global.EyeColorPreset, -1));
			break;				
		case EBodyPart::CLL:
		case EBodyPart::CLU:
		case EBodyPart::SHO:
		case EBodyPart::AEY:
		case EBodyPart::AHD:
			Wearables.Add(EditorDefaults->ConvertPdaToWearableDataRef(AssetInfo.Value, nullptr, -1));
			break;
		default:
			break;
			
		}
	}

	FString BodyMorph = EditorDefaults->GetBodyTypeMorphTarget(CharacterMetaDataRef.globalData.gender, CharacterMetaDataRef.globalData.bodyType).ToString();
	FString FaceMorph = EditorDefaults->GetPersonalityMorphTarget(CharacterMetaDataRef.globalData.gender, CharacterMetaDataRef.globalData.personality).ToString();

	if(!Character->Global.IsRobot)
	{
		CharacterMetaDataRef.wearables = Wearables;
		CharacterMetaDataRef.default_wearables = Wearables;
		CharacterMetaDataRef.customizableData = Customizables;

		CharacterMetaDataRef.globalData.gender = Character->Global.gender;
		CharacterMetaDataRef.globalData.personality = Character->Global.personality;
		CharacterMetaDataRef.globalData.bodyType = Character->Global.bodyType;
		CharacterMetaDataRef.globalData.skinTone = Character->Global.skinTone;

		CharacterMetaDataRef.globalData.bodyMesh = EditorDefaults->DefaultBodyMesh;

		CharacterMetaDataRef.globalData.textures.Add(FUnseenCharacterTextureRef("FAC", "Main", Character->GetFaceBodyTextures(CharacterMetaDataRef.globalData.gender, FaceMorph, false).texture));
		CharacterMetaDataRef.globalData.textures.Add(FUnseenCharacterTextureRef("BOD", "Main", Character->GetFaceBodyTextures(CharacterMetaDataRef.globalData.gender, BodyMorph, true).texture));
	
	}
	
	else
	{
		CharacterMetaDataRef.globalData.bodyMesh = EditorDefaults->DefaultRobotMesh;
		CharacterMetaDataRef.globalData.personality = EPersonalities::RobotDefault;
		FUnseenWearablesDataRef Face = EditorDefaults->GetFaceDataRow(Character->Global.gender, Character->Global.personality);
		FUnseenWearablesDataRef Body = EditorDefaults->GetBodyDataRow(Character->Global.gender, Character->Global.bodyType, Character->Global.IsRobot);
		CharacterMetaDataRef.globalData.textures.Add(FUnseenCharacterTextureRef("FAC", "Main", Face.texture));
		CharacterMetaDataRef.globalData.textures.Add(FUnseenCharacterTextureRef("BOD", "Main", Body.texture));
		CharacterMetaDataRef.globalData.textures.Add(FUnseenCharacterTextureRef("Screen", "Main", nullptr));
		
	}

	CharacterMetaDataRef.underwear = GenerateUnderwear(CharacterMetaDataRef);
	
	FUnseenCharacterMetaDataRef MetaDataRef = EditorDefaults->CollectMetaDataRef(Character->GlobalData, Character->CurrentAssetsInfo);
	FUnseenCharacterMetaData MetaData = EditorDefaults->ConvertCharacterRefToData(CharacterMetaDataRef, Character->Global.IsRobot);
	FPublicMetadata PublicMetadata = EditorDefaults->GeneratePublicMetaData(Metadata, Index, Character->Global, bIsFreemium);	
	
	JsonHandler->ExportCharMetaData(MetaDataRef, MetaData, PublicMetadata, Path, Index);
}

void UCharacterDataOperations::ExportStoreItems(TArray<FItemRarity> StoreItems, FString Path)
{
	int Counter = 0;
	UJsonHandler* JsonHandler = NewObject<UJsonHandler>();
	for(FItemRarity Item : StoreItems)
	{
		
		
		if (Item.Asset->BodyPart == EBodyPart::AEY || Item.Asset->BodyPart == EBodyPart::AHD)
		{
			Counter++;
			FUnseenWearablesDataRef DataRef = EditorDefaults->ConvertPdaToWearableDataRef(Item.Asset, nullptr, 0);
			FUnseenWearablesData AssetData = EditorDefaults->ConvertAssetInfoRefToData(DataRef);
			AssetData.wearable_id = FString::FromInt(Counter);
			JsonHandler->WriteAssetJSONRefToFile(Path, FString::Printf(TEXT("%d"), Counter), AssetData, Item.Asset->BodyPart,Item.Asset->MaterialType);
			FString Category = "";

			if(EditorDefaults->BodyPartCategories.Contains(Item.Asset->BodyPart))
			{
				Category = *EditorDefaults->BodyPartCategories.Find(Item.Asset->BodyPart);
			}
			FPublicMetadata AssetPublicMetadata = EditorDefaults->GenerateStorePublicMetadata(Counter, Category, ERarity::None);
			JsonHandler->SerializeStorePublicMetadata(*FString::Printf(TEXT("%s/json/%d"), *Path, Counter), AssetPublicMetadata, Counter);
		}
		else
		{
			for (ERarity Rarity : Item.Rarities)
			{
				Counter++;
				FUnseenWearablesDataRef DataRef = EditorDefaults->ConvertPdaToWearableDataRef(Item.Asset, nullptr, 0);
				FUnseenWearablesData AssetData = EditorDefaults->ConvertAssetInfoRefToData(DataRef);
				JsonHandler->WriteAssetJSONRefToFile(Path, FString::Printf(TEXT("%d"), Counter), AssetData, Item.Asset->BodyPart,Item.Asset->MaterialType);
				FString Category = "";

				if(EditorDefaults->BodyPartCategories.Contains(Item.Asset->BodyPart))
				{
					Category = *EditorDefaults->BodyPartCategories.Find(Item.Asset->BodyPart);
				}
				FPublicMetadata AssetPublicMetadata = EditorDefaults->GenerateStorePublicMetadata(Counter, Category, Rarity);			
				JsonHandler->SerializeStorePublicMetadata(*FString::Printf(TEXT("%s/json/%d"), *Path, Counter), AssetPublicMetadata, Counter);

			}
		}
	}
}
void UCharacterDataOperations::ExportCustomizableJSONByBodyPart(FString Path, EBodyPart BodyPart)
{
	if(EditorDefaults->BodyPartAssetInfoTables.Contains(BodyPart))
	{
		UDataTable* DataTable = *EditorDefaults->BodyPartAssetInfoTables.Find(BodyPart);
		TArray<FName> RowNames = DataTable->GetRowNames();
		for(int32 i =0; i<RowNames.Num(); i++)
		{
			FUnseenWearablesDataRef AssetInfo = EditorDefaults->GetAssetInfoFromTableByRowName(BodyPart, RowNames[i]);
			ExportAssetJSON(Path, i+1, AssetInfo, EUnseenMaterialType::FacialFeatures);
		}
	}
}

void UCharacterDataOperations::RunTexturePipeline()
{
	const FString PythonExe = TEXT("C:/Users/yourname/AppData/Local/Programs/Python/Python311/python.exe");
	const FString PythonScript = TEXT("\\\\192.168.3.11\\Character\\Scripts\\TextureDataBaseExporter - Works.py");

	// Parameters to pass
	const FString ExcelPath = TEXT("\\\\192.168.3.11\\Character\\YourExcelFolder\\DataSheet.xlsx");
	const FString SheetName = TEXT("Sheet2");
	const FString CodesReport = TEXT("C:/Temp/texture_codes_report.txt");
	const FString MainReport = TEXT("C:/Temp/asset_update_report.txt");

	// Compose command line string: "<script>" "<excel>" "<sheet>" "<codes_report>" "<main_report>"
	const FString CommandLine = FString::Printf(TEXT("\"%s\" \"%s\" \"%s\" \"%s\" \"%s\""),
		*PythonScript, *ExcelPath, *SheetName, *CodesReport, *MainReport);

	if (!FPaths::FileExists(PythonExe))
	{
		UE_LOG(LogTemp, Error, TEXT("Python executable not found at: %s"), *PythonExe);
		return;
	}

	if (!FPaths::FileExists(PythonScript))
	{
		UE_LOG(LogTemp, Error, TEXT("Python script not found at: %s"), *PythonScript);
		return;
	}

	FProcHandle ProcHandle = FPlatformProcess::CreateProc(
		*PythonExe,
		*CommandLine,
		true, false, false,
		nullptr, 0, NULL, NULL
	);

	if (ProcHandle.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Launched texture pipeline script with parameters."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to launch script."));
	}
}

FString UCharacterDataOperations::ValidateAssetsFromDataTables(
	const TMap<EBodyPart, UDataTable*>& DataTableMap,
	const FString& RootPath,
	bool LogFound,
	bool LogMissing,
	FString Name)
{
	if (DataTableMap.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ValidateAssetsFromDataTables: DataTableMap is empty."));
		return FString(); // return empty path
	}

	FString ReportLog;
	ReportLog += TEXT("=== Asset Validation Report ===\n\n");

	for (const TPair<EBodyPart, UDataTable*>& Entry : DataTableMap)
	{
		EBodyPart BodyPart = Entry.Key;
		UDataTable* DataTable = Entry.Value;

		if (!DataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("DataTable for BodyPart %s is null."), *UEnum::GetValueAsString(BodyPart));
			continue;
		}

		const FString BodyPartFolder = UEnum::GetValueAsString(BodyPart).RightChop(11);
		FString BodyPartLog;
		BodyPartLog += FString::Printf(TEXT("Asset Validation Report for BodyPart: %s\n\n"), *BodyPartFolder);

		TArray<FName> RowNames = DataTable->GetRowNames();
		bool bAnyLogged = false;

		for (const FName& RowName : RowNames)
		{
			const FDataLookup* Row = DataTable->FindRow<FDataLookup>(RowName, TEXT("ValidateAssets"));
			if (!Row || !Row->DataAsset) continue;

			UUnseenAssetData* Asset = Cast<UUnseenAssetData>(Row->DataAsset);
			if (!Asset) continue;

			FString AssetLog;
			bool bLoggedSomething = false;

			// Texture
			FString TexturePath;
			bool bTextureExists = false;

			if (Asset->Texture)
			{
				const FString TextureName = Asset->Texture->GetName();
				TArray<FString> TextureParts;
				TextureName.ParseIntoArray(TextureParts, TEXT("_"));

				FString TextureDir = RootPath;
				for (const FString& Part : TextureParts)
				{
					TextureDir = FPaths::Combine(TextureDir, Part);
				}

				TexturePath = FPaths::Combine(TextureDir, TextureName + TEXT(".jpg"));
				FPaths::NormalizeFilename(TexturePath);
				bTextureExists = FPaths::FileExists(TexturePath);

				if (bTextureExists && LogFound)
				{
					AssetLog += FString::Printf(TEXT("  ✅ Texture Found: %s\n"), *TexturePath);
					bLoggedSomething = true;
				}
				else if (!bTextureExists && LogMissing)
				{
					AssetLog += FString::Printf(TEXT("  ❌ Texture Missing: %s\n"), *TexturePath);
					bLoggedSomething = true;
				}
			}
			else
			{
				AssetLog += TEXT("  ⚠️  No Texture assigned.\n");
				bLoggedSomething = true;
			}

			// Mesh
			FString MeshPath;
			bool bMeshExists = false;

			if (Asset->GameMesh)
			{
				const FString MeshName = Asset->GameMesh->GetName();
				TArray<FString> MeshParts;
				MeshName.ParseIntoArray(MeshParts, TEXT("_"));

				FString MeshDir = RootPath;
				for (const FString& Part : MeshParts)
				{
					MeshDir = FPaths::Combine(MeshDir, Part);
				}

				MeshPath = FPaths::Combine(MeshDir, MeshName + TEXT(".glb"));
				FPaths::NormalizeFilename(MeshPath);
				bMeshExists = FPaths::FileExists(MeshPath);

				if (bMeshExists && LogFound)
				{
					AssetLog += FString::Printf(TEXT("  ✅ Mesh Found: %s\n"), *MeshPath);
					bLoggedSomething = true;
				}
				else if (!bMeshExists && LogMissing)
				{
					AssetLog += FString::Printf(TEXT("  ❌ Mesh Missing: %s\n"), *MeshPath);
					bLoggedSomething = true;
				}
			}
			else
			{
				AssetLog += TEXT("  ⚠️  No GameMesh assigned.\n");
				bLoggedSomething = true;
			}

			if (bLoggedSomething)
			{
				BodyPartLog += FString::Printf(TEXT("AssetID: %s\n%s\n"), *Asset->AssetID.ToString(), *AssetLog);
				bAnyLogged = true;
			}
		}

		if (bAnyLogged)
		{
			ReportLog += BodyPartLog;
			ReportLog += TEXT("------------------------------------------------------------\n\n");
		}
	}

	// ===== SAVE REPORT =====
	const FString ReportDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("AssetFolder/Report"));
	IFileManager::Get().MakeDirectory(*ReportDir, true);

	FString ReportPath = FPaths::Combine(ReportDir, Name + ".txt");
	ReportPath = FPaths::ConvertRelativePathToFull(ReportPath); // 🔧 convert to full path

	FFileHelper::SaveStringToFile(ReportLog, *ReportPath);

	UE_LOG(LogTemp, Log, TEXT("Asset validation report saved to: %s"), *ReportPath);

	return ReportPath;
}

void UCharacterDataOperations::OpenFolderInExplorer(const FString& FolderPath)
{
	if (FolderPath.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("OpenFolderInExplorer: FolderPath is empty."));
		return;
	}

	if (!IFileManager::Get().DirectoryExists(*FolderPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("OpenFolderInExplorer: Folder does not exist - %s"), *FolderPath);
		return;
	}

	FPlatformProcess::ExploreFolder(*FolderPath);
}


