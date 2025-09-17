// Fill out your copyright notice in the Description page of Project Settings.
#include "EditorDefaults.h"
#include "GameTypes.h"
#include "UnseenCollectionData.h"
#include "UnseenAssetData.h"

class UUnseenCollectionData;

// Data Table Getters //
#pragma region "Data Getters"

FUnseenWearablesDataRef UEditorDefaults::GetAssetInfoFromTableByRowName(EBodyPart BodyPart, FName RowName)
{
	if(BodyPartAssetInfoTables.Contains(BodyPart))
	{
		UDataTable* DataTable = *BodyPartAssetInfoTables.Find(BodyPart);
		if(!DataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("DataTable reference is null!"));
			return FUnseenWearablesDataRef();
		}

		const FString ContextString(TEXT("Asset Data Retrieval"));
		FUnseenWearablesDataRef* RowData = DataTable->FindRow<FUnseenWearablesDataRef>(RowName, ContextString);

		if(!RowData)
		{
			UE_LOG(LogTemp, Warning, TEXT("Row '%s' not found in DataTable!"), *RowName.ToString());
			return FUnseenWearablesDataRef();
		}
		return *RowData;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Body Part not found in Map!"));
		return FUnseenWearablesDataRef();
	}
}
FUnseenWearablesDataRef UEditorDefaults::GetAssetInfoFromTableByIndex(EBodyPart BodyPart, int32 Index)
{
	if(BodyPartAssetInfoTables.Contains(BodyPart))
	{
		UDataTable* DataTable = *BodyPartAssetInfoTables.Find(BodyPart);
		if(!DataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("DataTable reference is null!"));
			return FUnseenWearablesDataRef();
		}

		const FString ContextString(TEXT("Asset Data Retrieval"));

		TArray<FName> RowNames = DataTable->GetRowNames();

		if(!RowNames.IsValidIndex(Index))
		{
			return FUnseenWearablesDataRef();			
		}
		
		FUnseenWearablesDataRef* RowData = DataTable->FindRow<FUnseenWearablesDataRef>(RowNames[Index], ContextString);
		return *RowData;
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Body Part not found in Map!"));
		return FUnseenWearablesDataRef();
	}
}

FDataLookup UEditorDefaults::GetAssetPdaFromTableByIndex(EBodyPart BodyPart, int32 Index, ECharGender Gender)
{
	const TMap<EBodyPart, UDataTable*>& BodyPartPDATables = (Gender == ECharGender::Male) ? BodyPartPDATablesMale : BodyPartPDATablesFemale;
	if(BodyPartPDATables.Contains(BodyPart))
	{
		UDataTable* DataTable = *BodyPartPDATables.Find(BodyPart);
		if(!DataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("DataTable reference is null!"));
			return FDataLookup();
		}

		const FString ContextString(TEXT("Asset Data Retrieval"));

		TArray<FName> RowNames = DataTable->GetRowNames();

		if(!RowNames.IsValidIndex(Index))
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid Index! %d for body part: %s"), Index, *UEnum::GetValueAsString(BodyPart));
			return FDataLookup();			
		}
		
		FDataLookup* RowData = DataTable->FindRow<FDataLookup>(RowNames[Index], ContextString);
		return *RowData;
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Body Part %s not found in Map!"), *UEnum::GetValueAsString(BodyPart));
		return FDataLookup();
	}
}

FDataLookup UEditorDefaults::GetColorPdaFromTableByIndex(EBodyPart BodyPart, int32 Index)
{
	if(ColorPDATables.Contains(BodyPart))
	{
		UDataTable* DataTable = *ColorPDATables.Find(BodyPart);
		if(!DataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("DataTable reference is null!"));
			return FDataLookup();
		}

		const FString ContextString(TEXT("Asset Data Retrieval"));

		TArray<FName> RowNames = DataTable->GetRowNames();

		if(!RowNames.IsValidIndex(Index))
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid Index!"));
			return FDataLookup();			
		}
		
		FDataLookup* RowData = DataTable->FindRow<FDataLookup>(RowNames[Index], ContextString);
		return *RowData;
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Body Part %s not found in Color Map!"), *UEnum::GetValueAsString(BodyPart));
		return FDataLookup();
	}
}

FName UEditorDefaults::GetAssetInfoRowName(EBodyPart BodyPart, int32 Index)
{
	if(BodyPartAssetInfoTables.Contains(BodyPart))
	{
		UDataTable* DataTable = *BodyPartAssetInfoTables.Find(BodyPart);
		if(!(DataTable->GetRowNames().IsValidIndex(Index)))
		{
			return FName(*FString::Printf(TEXT("Invalid Entry (1 - %d)"), DataTable->GetRowNames().Num() ));

		}
		else
		{
			return DataTable->GetRowNames()[Index];
		}
	}
	else
	{
		return "Invalid Data Table";
	}
}
FUnseenColorPresetLinear UEditorDefaults::GetColorFromTableByIndex(EBodyPart BodyPart, int32 Index)
{
	if(ColorArrayTables.Contains(BodyPart))
	{
		UDataTable* DataTable = *ColorArrayTables.Find(BodyPart);
		if(!DataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("DataTable reference is null!"));
			return FUnseenColorPresetLinear(0, {}, {});
		}

		const FString ContextString(TEXT("Asset Data Retrieval"));

		TArray<FName> RowNames = DataTable->GetRowNames();

		if(!RowNames.IsValidIndex(Index))
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid Index!"));
			return FUnseenColorPresetLinear(0, {}, {});		
		}
		
		FUnseenColorPresetLinear* RowData = DataTable->FindRow<FUnseenColorPresetLinear>(RowNames[Index], ContextString);
		return *RowData;
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Body Part not found in Map!"));
		return FUnseenColorPresetLinear(0, {}, {});
	}
}
FName UEditorDefaults::GetPersonalityMorphTarget (ECharGender Gender, EPersonalities Personality)
{
	if(!PersonalityMorphTargetNames.Contains(Personality))
	{
		return "";
	}
	const FName* FoundPersonality = PersonalityMorphTargetNames.Find(Personality);
	if(Gender == ECharGender::None)
	{
		return "";
	}
	const FString GenderSuffix = (Gender == ECharGender::Male) ? TEXT("M") : TEXT("F");
	return FName(FoundPersonality ? (*FoundPersonality).ToString() + GenderSuffix : GenderSuffix);
}
FName UEditorDefaults::GetBodyTypeMorphTarget (ECharGender Gender, EBodyType BodyType)
{
	if(Gender == ECharGender::None)
	{
		return "";
	}	
	const TMap<EBodyType, FName>& BodyTypeMap = (Gender == ECharGender::Male ? MaleBodyMorphTargetNames : FemaleBodyMorphTargetNames);

	if(!BodyTypeMap.Contains(BodyType))
	{
		return "";
	}
	return BodyTypeMap.FindRef(BodyType);
}
FUnseenWearablesDataRef UEditorDefaults::GetFaceDataRow(ECharGender Gender, EPersonalities Personality)
{
	// Step 1: Get the GenderFaceTables map to find the corresponding DataTable
	UDataTable* FaceDataTable = GenderFaceTables.Contains(Gender) ? GenderFaceTables[Gender] : nullptr;
	if (!FaceDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("No Face DataTable found for Gender: %d"), static_cast<int32>(Gender));
		return FUnseenWearablesDataRef();
	}

	// Step 2: Get the Morph Target Name based on the personality
	FName MorphTargetName;
	if (PersonalityMorphTargetNames.Contains(Personality))
	{
		MorphTargetName = PersonalityMorphTargetNames[Personality];
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Morph Target Name found for Personality: %d"), static_cast<int32>(Personality));
		return FUnseenWearablesDataRef();
	}

	// Step 3: Append 'F' or 'M' to the Morph Target Name based on gender
	FString RowNameString = MorphTargetName.ToString();
	RowNameString.Append(Gender == ECharGender::Female ? TEXT("F") : TEXT("M"));
	FName RowName(*RowNameString);

	// Step 4: Get the row from the DataTable using the constructed Row Name
	FUnseenWearablesDataRef* DataRow = FaceDataTable->FindRow<FUnseenWearablesDataRef>(RowName, TEXT("GetFaceDataRow"), true);
	if (!DataRow)
	{
		UE_LOG(LogTemp, Error, TEXT("No row found in Face DataTable for Row Name: %s"), *RowName.ToString());
		return FUnseenWearablesDataRef();
	}

	// Step 5: Return the found row
	return *DataRow;
}
FUnseenWearablesDataRef UEditorDefaults::GetBodyDataRow(ECharGender Gender, EBodyType BodyType, bool IsRobot)
{
	// Step 1: Get the GenderBodyTables map to find the corresponding DataTable
	UDataTable* BodyDataTable = GenderBodyTables.Contains(Gender) ? GenderBodyTables[Gender] : nullptr;
	if (!BodyDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("No Body DataTable found for Gender: %d"), static_cast<int32>(Gender));
		return FUnseenWearablesDataRef();
	}

	// Step 2: Get the Morph Target Name based on the gender and body type
	FName MorphTargetName;
	if (Gender == ECharGender::Male && MaleBodyMorphTargetNames.Contains(BodyType))
	{
		if(!IsRobot)
		{MorphTargetName = MaleBodyMorphTargetNames[BodyType];}
		else
		{
			MorphTargetName = "ROBSM";
		}
	}
	else if (Gender == ECharGender::Female && FemaleBodyMorphTargetNames.Contains(BodyType))
	{
		if(!IsRobot)
		{
			MorphTargetName = FemaleBodyMorphTargetNames[BodyType];
		}
		else
		{
			MorphTargetName = "ROBSF";
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Morph Target Name found for Gender: %d and BodyType: %d"), static_cast<int32>(Gender), static_cast<int32>(BodyType));
		return FUnseenWearablesDataRef();
	}

	// Step 3: Get the row from the DataTable using the Morph Target Name
	FUnseenWearablesDataRef* DataRow = BodyDataTable->FindRow<FUnseenWearablesDataRef>(MorphTargetName, TEXT("GetBodyDataRow"), true);
	if (!DataRow)
	{
		UE_LOG(LogTemp, Error, TEXT("No row found in Body DataTable for Morph Target Name: %s"), *MorphTargetName.ToString());
		return FUnseenWearablesDataRef();
	}

	// Step 4: Return the found row
	return *DataRow;
}
FUnseenCollectionInfo UEditorDefaults::GetCollectionInfoByIndex(int32 Index)
{
	if (!Collections)
	{
		UE_LOG(LogTemp, Error, TEXT("DataTable reference is null!"));
		return FUnseenCollectionInfo(); // Return default struct if DataTable is null
	}

	// Get the list of row names from the DataTable
	const TArray<FName>& RowNames = Collections->GetRowNames();
    
	// Check if the index is valid
	if (!RowNames.IsValidIndex(Index))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Index %d! Must be between 0 and %d."), Index, RowNames.Num() - 1);
		return FUnseenCollectionInfo(); // Return default struct if index is invalid
	}

	// Retrieve the row name at the given index
	const FName RowName = RowNames[Index];

	// Context string for identifying the table during lookup
	const FString ContextString(TEXT("GetCollectionInfoByIndex"));

	// Retrieve the row using the row name
	FUnseenCollectionInfo* RowData = Collections->FindRow<FUnseenCollectionInfo>(RowName, ContextString, true);
	if (!RowData)
	{
		UE_LOG(LogTemp, Error, TEXT("Row not found for RowName: %s"), *RowName.ToString());
		return FUnseenCollectionInfo(); // Return default struct if the row is not found
	}

	// Return the dereferenced row data
	return *RowData;
}
int32 UEditorDefaults::GetAssetInfoRowIndex(EBodyPart BodyPart, FName RowName)
{
	// Check if the BodyPart exists in the map
	if (BodyPartAssetInfoTables.Contains(BodyPart))
	{
		UDataTable* DataTable = *BodyPartAssetInfoTables.Find(BodyPart);
		if (!DataTable)
		{
			UE_LOG(LogTemp, Error, TEXT("DataTable reference is null for BodyPart!"));
			return -1; // Return -1 to indicate an invalid index
		}

		// Get the row names from the DataTable
		const TArray<FName>& RowNames = DataTable->GetRowNames();

		// Find the index of the given row name
		int32 Index = RowNames.IndexOfByKey(RowName);

		// Check if the row was found
		if (Index != INDEX_NONE)
		{
			return Index; // Return the found index
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("RowName '%s' not found in DataTable!"), *RowName.ToString());
			return -1; // Return -1 to indicate the row was not found
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BodyPart not found in BodyPartAssetInfoTables!"));
		return -1; // Return -1 to indicate an invalid BodyPart
	}
}
TMap<EBodyPart, FUnseenColorPresetLinear> UEditorDefaults::GetDefaultColorPreset()
{
    TMap<EBodyPart, FUnseenColorPresetLinear> ColorPreset;

    if (DefaultWearableColorPresets.Contains(EBodyPart::CLU) &&
        DefaultWearableColorPresets.Contains(EBodyPart::CLL) &&
        DefaultWearableColorPresets.Contains(EBodyPart::SHO))
    {
        // Retrieve the data tables for CLU, CLL, and SHO
        UDataTable* CLUColorsDT = *DefaultWearableColorPresets.Find(EBodyPart::CLU);
        UDataTable* CLLColorsDT = *DefaultWearableColorPresets.Find(EBodyPart::CLL);
        UDataTable* SHOColorsDT = *DefaultWearableColorPresets.Find(EBodyPart::SHO);

        // Ensure the data tables are valid
        if (CLUColorsDT && CLLColorsDT && SHOColorsDT)
        {
            // Get a random index based on the smallest row count among the three data tables
            int32 MinRowCount = FMath::Min3(CLUColorsDT->GetRowMap().Num(),
                                            CLLColorsDT->GetRowMap().Num(),
                                            SHOColorsDT->GetRowMap().Num());
            int32 RandomIndex = FMath::RandRange(0, MinRowCount - 1);

            // Fetch entries by the random index and add them to the ColorPreset map
            FString RowName = FString::Printf(TEXT("%d"), RandomIndex);

            if (FUnseenColorPresetLinear* CLUEntry = CLUColorsDT->FindRow<FUnseenColorPresetLinear>(*RowName, TEXT("Lookup CLU")))
            {
                ColorPreset.Add(EBodyPart::CLU, *CLUEntry);
            }

            if (FUnseenColorPresetLinear* CLLEntry = CLLColorsDT->FindRow<FUnseenColorPresetLinear>(*RowName, TEXT("Lookup CLL")))
            {
                ColorPreset.Add(EBodyPart::CLL, *CLLEntry);
            }

            if (FUnseenColorPresetLinear* SHOEntry = SHOColorsDT->FindRow<FUnseenColorPresetLinear>(*RowName, TEXT("Lookup SHO")))
            {
                ColorPreset.Add(EBodyPart::SHO, *SHOEntry);
            }
        }
    }

    return ColorPreset;
}
FUnseenColorPresetLinear UEditorDefaults::GetDefaultWearableColorPreset (EBodyPart BodyPart, int32 Index)
{
	if(DefaultWearableColorPresets.Contains(BodyPart))
	{
		UDataTable* DataTable = *DefaultWearableColorPresets.Find(BodyPart);
		if(!DataTable)
		{
			UE_LOG(LogTemp, Warning, TEXT("DataTable reference is null!"));
			return FUnseenColorPresetLinear(0, {}, {});
		}
		
		const FString ContextString(TEXT("Asset Data Retrieval"));
		
		TArray<FName> RowNames = DataTable->GetRowNames();
		
		if(!RowNames.IsValidIndex(Index))
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid Index!"));
			return FUnseenColorPresetLinear(0, {}, {});		
		}
		
		FUnseenColorPresetLinear* RowData = DataTable->FindRow<FUnseenColorPresetLinear>(RowNames[Index], ContextString);
		if(!RowData)
		{
			return FUnseenColorPresetLinear(0, {}, {});
		}

		return *RowData;		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Body Part not found in Map!"));
		return FUnseenColorPresetLinear(0, {}, {});
	}
}
#pragma endregion
// Data Converters //
#pragma region "Data Converters"
FUnseenCharacterColor UEditorDefaults::ConvertUnseenColorToInt(FUnseenCharacterColorLinear LinearColor)
{
	UE_LOG(LogTemp, Error, TEXT("Color float is %f"), LinearColor.Color.R);
	FUnseenCharacterColor IntColor;
	IntColor.colorData.r = LinearColor.Color.R * 255.f;
	IntColor.colorData.g = LinearColor.Color.G * 255.f;
	IntColor.colorData.b = LinearColor.Color.B * 255.f;
	IntColor.name = LinearColor.Name;

	UE_LOG(LogTemp, Error, TEXT("Color int is %d"), IntColor.colorData.r);
	return IntColor;
}
FUnseenCharacterColorLinear UEditorDefaults::ConvertUnseenColorToLinear(FUnseenCharacterColor IntColor)
{
	FUnseenCharacterColorLinear ColorData;
	ColorData.Color.R = IntColor.colorData.r / 255.f;
	ColorData.Color.G = IntColor.colorData.g / 255.f;
	ColorData.Color.B = IntColor.colorData.b / 255.f;
	ColorData.Name = IntColor.name;

	return ColorData;
}
FName UEditorDefaults::FormatNftIdInfo(const FNftIdInfo& NftInfo)
{
	FString BodyPartName = UEnum::GetDisplayValueAsText(NftInfo.BodyPart).ToString();
	FString FormattedString = FString::Printf(TEXT("%s_%03d_%03d_%03d"),
		*BodyPartName,
		NftInfo.BodyPartMeshID,
		NftInfo.BodyPartTextureID,
		NftInfo.BodyPartColorID
	);
	return FName(FormattedString);
}
FUnseenCharacterGlobalData UEditorDefaults::ConvertGlobalDataRefToData(FUnseenCharacterGlobalDataRef GlobalDataRef, bool IsRobot)
{
	FUnseenCharacterGlobalData GlobalData;

	// Convert gender enum to string
	GlobalData.gender = UEnum::GetDisplayValueAsText(GlobalDataRef.gender).ToString();

	UE_LOG(LogTemp, Error, TEXT("%s"), *UEnum::GetDisplayValueAsText(GlobalDataRef.personality).ToString());

	// Find personality morph target name
	if (const FName* FoundPersonality = PersonalityMorphTargetNames.Find(GlobalDataRef.personality))
	{
		FString GenderSuffix = (GlobalDataRef.gender == ECharGender::Male) ? "M" : "F";
		GlobalData.personality = FoundPersonality->ToString() + GenderSuffix;
	}
	else
	{
		GlobalData.personality = "Missing Data";
	}

	GlobalData.MaterialType = UEnum::GetDisplayValueAsText(GlobalDataRef.MaterialType).ToString();
	
	GlobalData.bodyType = ConvertBodyTypeToString(GlobalDataRef.bodyType, GlobalDataRef.gender);
	if(GlobalDataRef.bodyMesh)
	{
		GlobalData.bodyMesh  = GlobalDataRef.bodyMesh->GetName() + ".glb";
	}
	FUnseenCharacterColorLinear SkinTone;
	SkinTone.Color = GlobalDataRef.skinTone;
	if(!IsRobot)
	{
		GlobalData.MaterialType = "Skin";
	}
	else
	{
		GlobalData.MaterialType = "Robot";
	}
	GlobalData.skinTone = ConvertUnseenColorToInt(SkinTone).colorData;
	if(GlobalDataRef.textures.Num()!=0)
	{
		for(FUnseenCharacterTextureRef TextureRef : GlobalDataRef.textures)
		{
			if(TextureRef.texture!=nullptr)
			{
				GlobalData.textures.Add(ConvertCharacterTextureRefToData(TextureRef));
			}
			else
			{
				GlobalData.textures.Add(FUnseenCharacterTexture(TextureRef.name, TextureRef.paramName, ""));
			}

		}
	}

	return GlobalData;
}
FString UEditorDefaults::ConvertBodyTypeToString(EBodyType BodyType, ECharGender Gender)
{
	switch (Gender)
	{
	case ECharGender::Male:
		if(MaleBodyMorphTargetNames.Contains(BodyType))
		{
			return MaleBodyMorphTargetNames.Find(BodyType)->ToString();
		}
		else
		{
			return "Missing Male Body Type Value";
		}
	case ECharGender::Female:
		if(FemaleBodyMorphTargetNames.Contains(BodyType))
		{
			return FemaleBodyMorphTargetNames.Find(BodyType)->ToString();
		}
		else
		{
			return "Missing Female Body Type Value";
		}
		default:
			return "";
	}
}

FString UEditorDefaults::ConvertPersonalityToString(EPersonalities Personality, ECharGender Gender)
{
	if(PersonalityMorphTargetNames.Contains(Personality))
	{	const FName* FoundPersonality = PersonalityMorphTargetNames.Find(Personality);
		const FString GenderSuffix = (Gender == ECharGender::Male) ? TEXT("M") : TEXT("F");
		const FName PersonalityMorphTarget = FName(FoundPersonality ? (*FoundPersonality).ToString() + GenderSuffix : GenderSuffix);
		return PersonalityMorphTarget.ToString();
	}
	else
	{
		return "Missing Male Body Type Value";
	}
}
FUnseenCharacterTexture UEditorDefaults::ConvertCharacterTextureRefToData(FUnseenCharacterTextureRef CharTextureRef)
{
	FUnseenCharacterTexture CharTextureData;
	CharTextureData.name = CharTextureRef.name;
	CharTextureData.paramName = CharTextureRef.paramName;
	CharTextureData.textureName = CharTextureRef.texture->GetName() + ".jpg";

	return CharTextureData;
}
FUnseenCharacterMetaData UEditorDefaults::ConvertCharacterRefToData(FUnseenCharacterMetaDataRef CharacterMetaDataRef, bool IsRobot)
{
	FUnseenCharacterMetaData CharacterMetaData;
	UE_LOG(LogTemp, Error, TEXT("%s"), *UEnum::GetDisplayValueAsText(CharacterMetaDataRef.globalData.personality).ToString());
	CharacterMetaData.globalData = ConvertGlobalDataRefToData(CharacterMetaDataRef.globalData, IsRobot);
	for(FUnseenWearablesDataRef AssetInfo : CharacterMetaDataRef.customizableData)
	{
		CharacterMetaData.customizableData.Add(ConvertAssetInfoRefToData(AssetInfo));
	}
	for(FUnseenWearablesDataRef AssetInfo : CharacterMetaDataRef.default_wearables)
	{
		CharacterMetaData.default_wearables.Add(ConvertAssetInfoRefToData(AssetInfo));
	}
	for(FUnseenWearablesDataRef AssetInfo : CharacterMetaDataRef.wearables)
	{
		CharacterMetaData.wearables.Add(ConvertAssetInfoRefToData(AssetInfo));
	}
	for(FUnseenWearablesDataRef AssetInfo : CharacterMetaDataRef.underwear)
	{
		CharacterMetaData.underwear.Add(ConvertAssetInfoRefToData(AssetInfo));
	}	
	return CharacterMetaData;
}
FUnseenCharacterMetaDataRef UEditorDefaults::CollectMetaDataRef(FUnseenCharacterGlobalDataRef GlobalDataRef,
	TMap<EBodyPart, FUnseenWearablesDataRef> CurrentAssetsInfo)
{
	FUnseenCharacterMetaDataRef CharacterMetaDataRef;

	CharacterMetaDataRef.globalData = GlobalDataRef;

	for(TPair<EBodyPart, FUnseenWearablesDataRef> AssetInfo : CurrentAssetsInfo)
	{
		switch(AssetInfo.Key)
		{
		case EBodyPart::HAI:
		case EBodyPart::EYB:
		case EBodyPart::EYE:
		case EBodyPart::FAH:
			CharacterMetaDataRef.customizableData.Add(AssetInfo.Value);
			break;
		case EBodyPart::CLL:
		case EBodyPart::CLU:
		case EBodyPart::SHO:
		case EBodyPart::AEY:
		case EBodyPart::AHD:
			CharacterMetaDataRef.wearables.Add(AssetInfo.Value);
			CharacterMetaDataRef.default_wearables.Add(AssetInfo.Value);
			break;
		default:
			break;
			
		}
	}	
	return CharacterMetaDataRef;
}
FUnseenWearablesData UEditorDefaults::ConvertAssetInfoRefToData(FUnseenWearablesDataRef AssetInfo)
{
	FUnseenWearablesData AssetData;
	AssetData.collection_id = AssetInfo.collection_id;
	AssetData.wearable_id = AssetInfo.wearable_id;
	AssetData.colorPresetIndex = AssetInfo.colorPresetIndex;
	AssetData.bIsBodyTypeTexture = AssetInfo.bIsBodyTypeTexture;
	if(AssetInfo.mesh)
	{AssetData.mesh = AssetInfo.mesh->GetName() + ".glb";}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Mesh Missing for %s"), *AssetInfo.wearable_id)
	}
	if(AssetInfo.texture)
	{AssetData.texture = AssetInfo.texture->GetName()+".jpg";}
	AssetData.bodyPart = UEnum::GetDisplayValueAsText(AssetInfo.bodyPart).ToString();
	AssetData.materialType = UEnum::GetDisplayValueAsText(AssetInfo.materialType).ToString();
	AssetData.materialValues = AssetInfo.materialValues;
	for(FUnseenCharacterColorLinear Color : AssetInfo.colors)
	{
		AssetData.colors.Add(ConvertUnseenColorToInt(Color));
	}	
	return AssetData;
}

FPublicMetadata UEditorDefaults::GeneratePublicMetaData(FPublicMetadata Metadata, int32 Index, FUnseenPresetGlobalData GlobalData, bool bIsFreemium)
{
	if(bIsFreemium)
	{
		if(GlobalData.gender == ECharGender::Male)
		{
			Metadata.Name = "Male #0" + FString::FromInt(Index) + "";
		}
		else
		{
			Metadata.Name = "Female #0" + FString::FromInt(Index) + "";
		}
		Metadata.Description = "Freemium characters available for free gameplay, offering a taste of the adventure without commitment.";
		Metadata.Image =  "https://dev.assets.rektgames.io/freemium/assets/images/0" + FString::FromInt(Index) + ".jpg";
	}
	else
	{
		Metadata.Name = "The Generates #" + FString::FromInt(Index) + "";
		Metadata.Image =  "https://dev.assets.rektgames.io/thegenerates/assets/images/" + FString::FromInt(Index) + ".jpg";
	}

	Metadata.Season = 1;
	Metadata.Attributes.Add(FPublicMetadataAttributes(
		"Level", "1"));

		Metadata.Attributes.Add(FPublicMetadataAttributes("Gender", UEnum::GetDisplayValueAsText(GlobalData.gender).ToString()));
	FString PersonalityName;
	if(PersonalityNamesMap.Contains(GlobalData.personality))
	{
		PersonalityName = *PersonalityNamesMap.Find(GlobalData.personality);
	}
	
	Metadata.Attributes.Add(FPublicMetadataAttributes("Personality", PersonalityName));

	return Metadata;
}

TArray<FUnseenCharacterColorLinear> UEditorDefaults::ConvertPresetToColorArray(FUnseenColorPresetLinear ColorPreset)
{
	TArray<FUnseenCharacterColorLinear> Colors;
	for(FUnseenCharacterColorLinear Color : ColorPreset.PresetColors)
	{
		Colors.Add(Color);
	}

	return Colors;
}
#pragma endregion

TArray<FName> UEditorDefaults::GetColorArrayRowNames(const EBodyPart BodyPart)
{
	TArray<FName> RowNames;

	// Get the DataTable for the given BodyPart
	UDataTable* DataTable = GetDataTableFromPDA(BodyPart, false, ECharGender::Male); // 'false' indicates it's a ColorArrayTable
	if (!DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("ColorArray DataTable for BodyPart %s is null or not found!"),
			   *UEnum::GetDisplayValueAsText(BodyPart).ToString());
		return RowNames; // Return empty array
	}

	// Get all row names from the DataTable
	RowNames = DataTable->GetRowNames();

	return RowNames;
}


TArray<FName> UEditorDefaults::GetRowNames(const EBodyPart BodyPart, ECharGender Gender)
{
	TArray<FName> RowNames;

	// Get the DataTable for the given BodyPart
	UDataTable* DataTable = GetDataTableFromPDA(BodyPart, true, Gender); // 'true' indicates it's an AssetInfoTable
	if (!DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable for BodyPart %s is null or not found!"),
			   *UEnum::GetDisplayValueAsText(BodyPart).ToString());
		return RowNames; // Return empty array
	}

	// Get all row names from the DataTable
	RowNames = DataTable->GetRowNames();

	return RowNames;
}

UDataTable* UEditorDefaults::GetDataTableFromPDA(const EBodyPart BodyPart, bool bIsAssetInfo, ECharGender Gender)
{

	const TMap<EBodyPart, UDataTable*>& BodyPartPDATables = (Gender == ECharGender::Male) ? BodyPartPDATablesMale : BodyPartPDATablesFemale;
	const TMap<EBodyPart, UDataTable*>& DataTableMap = bIsAssetInfo ? BodyPartPDATables : ColorPDATables;

	if (!DataTableMap.Contains(BodyPart))
	{
		UE_LOG(LogTemp, Warning, TEXT("BodyPart %s not found in DataTableMap!"), *UEnum::GetDisplayValueAsText(BodyPart).ToString());
		return nullptr;
	}

	return DataTableMap[BodyPart];
}

TArray<FName> UEditorDefaults::GetFaceRowNames(ECharGender Gender)
{
	TArray<FName> RowNames;

	// Retrieve FaceDT directly using the Gender key
	UDataTable** FoundDataTable = GenderFaceTables.Find(Gender);
	UDataTable* FaceDT = FoundDataTable ? *FoundDataTable : nullptr;

	if (!FaceDT)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Faces DataTable is null or not found in PDA!"),
			*UEnum::GetDisplayValueAsText(Gender).ToString());
		return RowNames; // Return empty RowNames
	}

	// Retrieve row names from the DataTable
	RowNames = FaceDT->GetRowNames();
	return RowNames;
}

TArray<FName> UEditorDefaults::GetSkinToneRowNames()
{
	TArray<FName> RowNames;

	if (!SkinTones)
	{
		UE_LOG(LogTemp, Warning, TEXT("Skintones DataTable or not found in PDA!"));
		return RowNames;
	}

	RowNames = SkinTones->GetRowNames();
	return RowNames;
}

EPersonalities UEditorDefaults::IndexToPersonality(int32 Index)
{
	if(!IndexToPersonalityMap.Contains(Index))
	{
		return EPersonalities::NoCoiner;
	}	
	return *IndexToPersonalityMap.Find(Index);
}

FUnseenColorPreset UEditorDefaults::ConvertColorPresetLinearToInt(FUnseenColorPresetLinear PresetLinear)
{
	FUnseenColorPreset Preset;

	Preset.PresetIndex = PresetLinear.PresetIndex;

	for(FUnseenCharacterColorLinear Color : PresetLinear.IconColors)
	{
		Preset.IconColors.Add(ConvertUnseenColorToInt(Color));
	}
	
	for(FUnseenCharacterColorLinear Color : PresetLinear.PresetColors)
	{
		Preset.PresetColors.Add(ConvertUnseenColorToInt(Color));
	}
	
	return Preset;
}

FUnseenWearablesDataRef UEditorDefaults::GetAndConvertPdaToDataRefFromIndex(EBodyPart BodyPart, int32 AssetIndex, int32 ColorIndex, ECharGender Gender)
{
	FUnseenWearablesDataRef AssetDataRef;

	UUnseenAssetData* AssetPda = Cast<UUnseenAssetData>(GetAssetPdaFromTableByIndex(BodyPart, AssetIndex, Gender).DataAsset);
	UUnseenColorPresetData* ColorPda = Cast<UUnseenColorPresetData>(GetColorPdaFromTableByIndex(BodyPart, ColorIndex).DataAsset);
	if(AssetPda)
	{
		AssetDataRef = ConvertPdaToWearableDataRef(AssetPda, ColorPda, ColorIndex);
		UE_LOG(LogTemp, Error, TEXT("Mesh is %s"), *AssetPda->GameMesh->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PDA Missing"));
	}
	AssetDataRef.wearable_id = FString::FromInt(AssetIndex);
	return AssetDataRef;
}
FUnseenWearablesDataRef UEditorDefaults::ConvertPdaToWearableDataRef(UUnseenAssetData* AssetPda, UUnseenColorPresetData* ColorPda, int32 ColorIndex)
{
	FUnseenWearablesDataRef AssetDataRef;
	AssetDataRef.wearable_id = AssetPda->AssetID.ToString();
	AssetDataRef.materialType = AssetPda->MaterialType;
	AssetDataRef.bodyPart = AssetPda->BodyPart;
	AssetDataRef.mesh = AssetPda->GameMesh;
	UE_LOG(LogTemp, Warning, TEXT("PDA Mesh is %s"), *AssetDataRef.mesh->GetName());
	AssetDataRef.texture = AssetPda->Texture;
	AssetDataRef.materialValues = AssetPda->MaterialValues;
	AssetDataRef.bIsBodyTypeTexture = AssetPda->bIsBodyTypeTexture;
	
	if(ColorIndex != -1 && ColorPda)
	{
		AssetDataRef.colorPresetIndex = ColorPda->PresetIndex;
		AssetDataRef.colors = ColorPda->PresetColors;
	}
	else
	{
		AssetDataRef.colors = AssetPda->Colors;
	}

	return AssetDataRef;
}


TArray<FUnseenWearablesDataRef> UEditorDefaults::GetAndConvertCollectionToDataRefFromIndex(FName RowName)
{
	TArray<FUnseenWearablesDataRef> NftAssetDataRef;


	const FString ContextString(TEXT("Asset Data Retrieval"));
	UUnseenCollectionData* CollectionData = Cast<UUnseenCollectionData>(Collections->FindRow<FDataLookup>(RowName, ContextString)->DataAsset);

	for(TPair<EBodyPart, UUnseenAssetData*> Nft :CollectionData->Nfts)
	{
		UUnseenAssetData* AssetPda = Nft.Value;
		FUnseenWearablesDataRef AssetDataRef;
		AssetDataRef.wearable_id = AssetPda->AssetID.ToString();
		AssetDataRef.materialType = AssetPda->MaterialType;
		AssetDataRef.bodyPart = AssetPda->BodyPart;
		AssetDataRef.mesh = AssetPda->GameMesh;
		AssetDataRef.texture = AssetPda->Texture;
		AssetDataRef.materialValues = AssetPda->MaterialValues;
		AssetDataRef.colors = AssetPda->Colors;

		NftAssetDataRef.Add(AssetDataRef);
	}		

	return NftAssetDataRef;
}


FPublicMetadata UEditorDefaults::GenerateStorePublicMetadata(int Index,FString Category, ERarity Rarity)
{
	FPublicMetadata Metadata;
	Metadata.Name = "Unseen Store #" + FString::FromInt(Index);
	Metadata.Image = "https://dev.assets.rektgames.io/rektstore/assets/images/" + FString::FromInt(Index) + ".jpg";
	Metadata.Description = "A captivating selection of rare in-game assets and apparel, designed to elevate your digital adventures with style and exclusivity.";
	Metadata.Season = 1;
	Metadata.Attributes.Add(FPublicMetadataAttributes(
		"Category", Category));
	Metadata.Attributes.Add(FPublicMetadataAttributes("Item Type", "FilteringCategoryToBeDetermined"));
	Metadata.Attributes.Add(FPublicMetadataAttributes("Rarity", UEnum::GetDisplayValueAsText(Rarity).ToString()));

	return Metadata;
}