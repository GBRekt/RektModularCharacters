// Fill out your copyright notice in the Description page of Project Settings.
#include "UnseenCharacter.h"

#include "BattlePassData.h"
#include "JsonHandler.h"
#include "ShaderCompiler.h"
#include "UnseenAssetData.h"
#include "UnseenCharacterPresetData.h"
#include "UnseenCollectionData.h"
#include "UnseenColorPresetData.h"
#include "UnseenSocialMediaCharData.h"
#include "Components/MeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"



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

// Sets default values
AUnseenCharacter::AUnseenCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root = CreateDefaultSubobject<USceneComponent>("Root");
	SkeletalDriver = CreateDefaultSubobject<USkeletalMeshComponent>("AnimationDriver");
	RootComponent = SkeletalDriver;
	//SkeletalDriver->SetupAttachment(Root);
	AHD = CreateDefaultSubobject<UUnseenBodyPart>("Headgear");
	AHD->SetupAttachment(SkeletalDriver);
	//AHD->SetLeaderPoseComponent(SkeletalDriver);
	AEY = CreateDefaultSubobject<UUnseenBodyPart>("Glasses");
	AEY->SetupAttachment(SkeletalDriver);
	//AEY->SetLeaderPoseComponent(SkeletalDriver);
	SHO = CreateDefaultSubobject<UUnseenBodyPart>("Shoes");
	SHO->SetupAttachment(SkeletalDriver);
	//SHO->SetLeaderPoseComponent(SkeletalDriver);
	CLL = CreateDefaultSubobject<UUnseenBodyPart>("Pants");
	CLL->SetupAttachment(SkeletalDriver);
	//CLL->SetLeaderPoseComponent(SkeletalDriver);
	CLU = CreateDefaultSubobject<UUnseenBodyPart>("Shirt");
	CLU->SetupAttachment(SkeletalDriver);
	//CLU->SetLeaderPoseComponent(SkeletalDriver);
	BOD = CreateDefaultSubobject<UUnseenBodyPart>("Body");
	BOD->SetupAttachment(SkeletalDriver);
	//BOD->SetLeaderPoseComponent(SkeletalDriver);
	EYE = CreateDefaultSubobject<UUnseenBodyPart>("Eyes");
	EYE->SetupAttachment(SkeletalDriver);
	//EYE->SetLeaderPoseComponent(SkeletalDriver);
	HAI = CreateDefaultSubobject<UUnseenBodyPart>("Hair");
	HAI->SetupAttachment(SkeletalDriver);
	//HAI->SetLeaderPoseComponent(SkeletalDriver);
	EYB = CreateDefaultSubobject<UUnseenBodyPart>("Eyebrows");
	EYB->SetupAttachment(SkeletalDriver);
	//EYB->SetLeaderPoseComponent(SkeletalDriver);
	FAH = CreateDefaultSubobject<UUnseenBodyPart>("Facial Hair");
	FAH->SetupAttachment(SkeletalDriver);
	//FAH->SetLeaderPoseComponent(SkeletalDriver);

	BodyPartsArray.Add(AHD);
	BodyPartsArray.Add(AEY);
	BodyPartsArray.Add(SHO);
	BodyPartsArray.Add(CLL);
	BodyPartsArray.Add(CLU);
	BodyPartsArray.Add(BOD);
	BodyPartsArray.Add(EYE);
	BodyPartsArray.Add(EYB);
	BodyPartsArray.Add(FAH);
	BodyPartsArray.Add(HAI);
}
// Called when the game starts or when spawned
void AUnseenCharacter::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void AUnseenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


TArray<FPermutationIndices> AUnseenCharacter::SplitShuffleChopResults(TArray<FPermutationIndices> Permutations)
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
TArray<FUnseenWearablesDataRef> AUnseenCharacter::GenerateDefaultsPda(int32 ColorIndex)
{
	TArray<FUnseenWearablesDataRef> DefaultWearables;
	DefaultWearables.Add( EditorDefaults->GetAndConvertPdaToDataRefFromIndex(EBodyPart::CLU,0, ColorIndex, ECharGender::Male));
	DefaultWearables.Add( EditorDefaults->GetAndConvertPdaToDataRefFromIndex(EBodyPart::CLL,0, ColorIndex, ECharGender::Male));
	DefaultWearables.Add( EditorDefaults->GetAndConvertPdaToDataRefFromIndex(EBodyPart::SHO,0, ColorIndex, ECharGender::Male));
	
	return DefaultWearables;
}

//----------------------Helpers----------------------------//
UUnseenAssetData* AUnseenCharacter::PickDataAsset(EBodyPart BodyPart){
	UUnseenAssetData* DataAssetToLoad;
	if(MasterPreset && LoadFromMasterPreset)
	{
		if(MasterPreset->Global.LoadFromCollection
			&& MasterPreset->Global.CollectionData
			&& MasterPreset->Global.CollectionData->Nfts.Contains(BodyPart))
		{
			if(!MasterPreset->BodyPartData.Find(BodyPart)->OverrideAsset)
			{
				DataAssetToLoad = *MasterPreset->Global.CollectionData->Nfts.Find(BodyPart);
			}
			else
			{
				DataAssetToLoad = MasterPreset->BodyPartData.Find(BodyPart)->Data;
			}
		}
		else
		{
			DataAssetToLoad = MasterPreset->BodyPartData.Find(BodyPart)->Data;
		}
	}
	else
	{
		if(Global.CollectionData && Global.LoadFromCollection && Global.CollectionData->Nfts.Contains(BodyPart))
		{
			if(!BodyPartData.Find(BodyPart)->OverrideAsset)
			{
				DataAssetToLoad = *Global.CollectionData->Nfts.Find(BodyPart);
			}
			else
			{
				DataAssetToLoad = BodyPartData.Find(BodyPart)->Data;
			}
		}
		else
		{
			DataAssetToLoad = BodyPartData.Find(BodyPart)->Data;
		}
	}
	return DataAssetToLoad;
}
UUnseenColorPresetData* AUnseenCharacter::PickColorPdaPreset(EBodyPart BodyPart)
{
	UUnseenColorPresetData* DataAssetToLoad;
	if(MasterPreset && LoadFromMasterPreset)
	{
		if(MasterPreset->BodyPartData.Find(BodyPart)->OverrideColorPreset)
		{
			DataAssetToLoad = MasterPreset->BodyPartData.Find(BodyPart)->ColorPreset;
		}
		else
		{
			switch (BodyPart)
			{
			case EBodyPart::HAI:
			case EBodyPart::EYB:
			case EBodyPart::FAH:
				DataAssetToLoad = MasterPreset->Global.HairColorPreset;
				break;
			case EBodyPart::EYE:
				DataAssetToLoad = MasterPreset->Global.EyeColorPreset;
				break;
			default:
				DataAssetToLoad = nullptr;
				break;
			}
		}
	}
	else
	{
		if(BodyPartData.Find(BodyPart)->OverrideColorPreset)
		{
			DataAssetToLoad = BodyPartData.Find(BodyPart)->ColorPreset;
		}
		else
		{
			switch (BodyPart)
			{
			case EBodyPart::HAI:
			case EBodyPart::EYB:
			case EBodyPart::FAH:
				DataAssetToLoad = Global.HairColorPreset;
				break;
			case EBodyPart::EYE:
				DataAssetToLoad = Global.EyeColorPreset;
				break;
			default:
				DataAssetToLoad = nullptr;
				break;
			}
		}
	}
	return DataAssetToLoad;
}
UUnseenBodyPart* AUnseenCharacter::ReturnBodyPart(EBodyPart BodyPart)
{
	switch (BodyPart)
	{
	case EBodyPart::BOD:
		return BOD;
	case EBodyPart::EYE:
		return EYE;
	case EBodyPart::HAI:
		return HAI;
	case EBodyPart::EYB:
		return EYB;
	case EBodyPart::FAH:
		return FAH;
	case EBodyPart::CLL:
		return CLL;
	case EBodyPart::CLU:
		return CLU;
	case EBodyPart::SHO:
		return SHO;
	case EBodyPart::AEY:
		return AEY;
	case EBodyPart::AHD:
		return AHD;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Invalid BodyPart: %d"), static_cast<int32>(BodyPart));
		return nullptr;
	}
}

FUnseenCharacterMetaDataRef AUnseenCharacter::ConvertIndicesToPda(FPermutationIndices CharacterIndices)
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
	FUnseenWearablesDataRef Body = EditorDefaults->GetBodyDataRow(Character.globalData.gender , Character.globalData.bodyType, Global.IsRobot);
	
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
	if(Character.globalData.gender == ECharGender::Male)
	{
		for(int32 i = 0; i<EditorDefaults->UnderwearMale.Num(); i++)
		{
			UUnseenAssetData* Underwear = EditorDefaults->UnderwearMale[i];
			Character.underwear.Add(EditorDefaults->ConvertPdaToWearableDataRef(Underwear, nullptr, -1));
		}
	}
	else
	{
		for(int32 i = 0; i<EditorDefaults->UnderwearFemale.Num(); i++)
		{
			UUnseenAssetData* Underwear = EditorDefaults->UnderwearFemale[i];
			Character.underwear.Add(EditorDefaults->ConvertPdaToWearableDataRef(Underwear, nullptr, -1));
		}
	}

	return Character;
}

//------------------------Character Updaters------------------------//
void AUnseenCharacter::UpdateBodyPartsFromPDA()
{
	UpdateBody();
	if(!IsSocialMedia)
	{UpdateSkin();}
	
	if(MasterPreset&&LoadFromMasterPreset)
	{
		MasterGlobal = MasterPreset->Global;
		MasterBodyPartData = MasterPreset->BodyPartData;
	}
	for(TPair<EBodyPart,FBodyPartDataInfo> DataInfo : BodyPartData)
	{
		UUnseenBodyPart* SkelMesh = ReturnBodyPart(DataInfo.Key);
		UMaterial* MaterialNeeded;

		UUnseenAssetData* DataAsset = PickDataAsset(DataInfo.Key);
		if(DataAsset)
		{
			switch(DataAsset->MaterialType)
			{
			case EUnseenMaterialType::Wearables:
				MaterialNeeded = EditorDefaults->WearableMaterial;
				break;
			case EUnseenMaterialType::Custom:
				MaterialNeeded = EditorDefaults->WearableMaterial;
				break;
				
			case EUnseenMaterialType::FacialFeatures:
				MaterialNeeded = EditorDefaults->FacialFeaturesMaterial;
				break;
			default:
				MaterialNeeded = EditorDefaults->SkinMaterial;
				break;
			}
			CurrentCharacter.Add(DataInfo.Key, DataAsset);
			UE_LOG(LogTemp, Error, TEXT("%s"), *DataAsset->GetName());
			UUnseenColorPresetData* ColorPreset = PickColorPdaPreset(DataInfo.Key);
			if(Global.IsRobot)
			{
				switch (DataAsset->BodyPart)
				{
				case EBodyPart::CLL:
				case EBodyPart::CLU:
				case EBodyPart::SHO:
					SkelMesh->UpdateFromPDA(DataAsset, ColorPreset, MaterialNeeded, IsSocialMedia);
					break;
				default:
					SkelMesh->ClearMesh();
					break;
				}
			}
			else
			{
				if(DataInfo.Value.Active)
				{

					SkelMesh->UpdateFromPDA(DataAsset, ColorPreset, MaterialNeeded, IsSocialMedia);				
				}
				else
				{
					SkelMesh->ClearMesh();
				}
			}

		}
		else
		{
			SkelMesh->ClearMesh();
		}

		if(!IsSocialMedia)
		{UpdateSkinMasks(DataAsset, DataInfo.Value.Active);}

	}

	if(IsSocialMedia)
	{
		UpdateSocialMediaHair();
		UpdateSocialMediaMaterials();
	}
	
	UpdateComponentsMorphTargets();
}
void AUnseenCharacter::UpdateComponentsMorphTargets()
{
	FUnseenPresetGlobalData LocalGlobal;
	if(MasterPreset && LoadFromMasterPreset)
	{
		LocalGlobal = MasterPreset->Global;
	}
	else
	{
		LocalGlobal = Global;
	}
	FName BodyMorphTarget = EditorDefaults->GetBodyTypeMorphTarget(LocalGlobal.gender, LocalGlobal.bodyType);
	UE_LOG(LogTemp, Warning, TEXT("Morph target is %s"), *BodyMorphTarget.ToString());
	FName PersonalityMorphTarget = EditorDefaults->GetPersonalityMorphTarget(LocalGlobal.gender, LocalGlobal.personality);
	for(UUnseenBodyPart* BodyPart : BodyPartsArray)
	{
		BodyPart->ClearMorphTargets();
		BodyPart->SetMorphTarget(BodyMorphTarget, 1.f);
		BodyPart->SetMorphTarget(PersonalityMorphTarget, 1.f);
	}
}
void AUnseenCharacter::UpdateSkinMasks(UUnseenAssetData* AssetData, bool IsActive)
{
	if(!Global.IsRobot)
	{
		if(AssetData)
		{
			UTexture* MaskTexture;
			FName BodyPart;
	
			switch(AssetData->BodyPart)
			{
			case EBodyPart::CLU:
			case EBodyPart::CLL:
			case EBodyPart::SHO:
				BodyPart = FName(*UEnum::GetDisplayValueAsText(AssetData->BodyPart).ToString());
				MaskTexture = AssetData->Texture;			
				if(IsActive)
				{
					if(MaskTexture)
					{
						BodyMaterial->SetTextureParameterValue(BodyPart, MaskTexture);
					}
				}
				else
				{
					BodyMaterial->SetTextureParameterValue(BodyPart, EditorDefaults->WhiteTexture);
				}
				break;
			default:
				break;
		
			}
		}
	}
}
void AUnseenCharacter::UpdateSkin()
{
	if(Global.IsRobot)
	{
		BodyMaterial = UMaterialInstanceDynamic::Create(EditorDefaults->RobotMaterial, this);
		FaceMaterial = UMaterialInstanceDynamic::Create(EditorDefaults->RobotMaterial, this);

		BOD->SetMaterial(0, FaceMaterial);
		BOD->SetMaterial(1, BodyMaterial);
		FUnseenWearablesDataRef Face = EditorDefaults->GetFaceDataRow(Global.gender, Global.personality);
		FUnseenWearablesDataRef Body = EditorDefaults->GetBodyDataRow(Global.gender, Global.bodyType, Global.IsRobot);
		FaceMaterial->SetTextureParameterValue("Main", Face.texture);
		BodyMaterial->SetTextureParameterValue("Main", Body.texture);
		FaceMaterial->SetVectorParameterValue("SkinTone", Global.skinTone);
		BodyMaterial->SetVectorParameterValue("SkinTone", Global.skinTone);
		
	}
	else
	{
		if(!IsSocialMedia)
		{
			if(BodyMaterial == nullptr)
			{
				BodyMaterial = UMaterialInstanceDynamic::Create(EditorDefaults->SkinMaterial, this);
			}

			if(FaceMaterial == nullptr)
			{
				FaceMaterial = UMaterialInstanceDynamic::Create(EditorDefaults->SkinMaterial, this);
			}

			FUnseenWearablesDataRef Face = EditorDefaults->GetFaceDataRow(Global.gender, Global.personality);
			FUnseenWearablesDataRef Body = EditorDefaults->GetBodyDataRow(Global.gender, Global.bodyType, Global.IsRobot);
			FaceMaterial->SetTextureParameterValue("Main", Face.texture);
			BodyMaterial->SetTextureParameterValue("Main", Body.texture);
			FaceMaterial->SetVectorParameterValue("SkinTone", Global.skinTone);
			BodyMaterial->SetVectorParameterValue("SkinTone", Global.skinTone);

			BodyMaterial->SetScalarParameterValue("HasMasks", 1.0);

			BOD->SetMaterial(0, FaceMaterial);
			BOD->SetMaterial(1, BodyMaterial);

			GlobalData.skinTone = Global.skinTone;
			GlobalData.textures.Empty();
			GlobalData.textures.Add(FUnseenCharacterTextureRef("FAC", "Main", Face.texture));
			GlobalData.textures.Add(FUnseenCharacterTextureRef("BOD", "Main", Body.texture));
		}
		else
		{
			UMaterialInstanceDynamic* SkinMaterial = UMaterialInstanceDynamic::Create(EditorDefaults->SocialMediaSkinMaterial, this);
			BOD->SetMaterial(0, SkinMaterial);
			BOD->SetMaterial(1, SkinMaterial);
		}
	}

}
void AUnseenCharacter::UpdateBody()
{
	if(IsSocialMedia)
	{
		UUnseenSocialMediaCharData* CharData = *EditorDefaults->SocialMediaDataMap.Find(Global.personality);
		CurrentSocialMediaChar = CharData;
		if(CharData)
		{
			UE_LOG(LogTemp, Warning, TEXT("Char Data Found"));
			if(Global.gender == ECharGender::Male)
			{
				if(CharData->Male.Body)
				{UE_LOG(LogTemp, Warning, TEXT("Skeletal Male Found"));
					BOD->SetSkeletalMesh(CharData->Male.Body);
				}
			}
			else
			{
				if(CharData->Female.Body)
				{
					UE_LOG(LogTemp, Warning, TEXT("Skeletal Female Found"));
					BOD->SetSkeletalMesh(CharData->Female.Body);
				}
			}
		}
	}
	else
	{
		if(Global.IsRobot)
		{
			BOD->SetSkeletalMesh(EditorDefaults->DefaultRobotMesh);
		}
		else
		{
			BOD->SetSkeletalMesh(EditorDefaults->DefaultBodyMesh);
		}
		
	}
}
void AUnseenCharacter::UpdateSocialMediaHair()
{
	FString HairName = "";
	FString FacialHairName = "";


	if(CurrentSocialMediaChar)
	{	
		if(Global.gender==ECharGender::Male)
		{
			if(CurrentSocialMediaChar->Male.Hair.IsValidIndex(SocialMediaHairIndex))
			{
				HAI->SetSkeletalMesh(CurrentSocialMediaChar->Male.Hair[SocialMediaHairIndex]);
				HairName = CurrentSocialMediaChar->Male.Hair[SocialMediaHairIndex]->GetName();
			}
			else
			{
				SocialMediaHairIndex = CurrentSocialMediaChar->Male.Hair.Num()-1;
				HAI->SetSkeletalMesh(CurrentSocialMediaChar->Male.Hair[SocialMediaHairIndex]);
				HairName = CurrentSocialMediaChar->Male.Hair[SocialMediaHairIndex]->GetName();
			}
				
			if(CurrentSocialMediaChar->Male.FacialHair.IsValidIndex(SocialMediaFacialHairIndex))
			{
				FAH->SetSkeletalMesh(CurrentSocialMediaChar->Male.FacialHair[SocialMediaFacialHairIndex]);
				FacialHairName = CurrentSocialMediaChar->Male.FacialHair[SocialMediaFacialHairIndex]->GetName();
			}
			else
			{
				SocialMediaFacialHairIndex = CurrentSocialMediaChar->Male.FacialHair.Num()-1;
				FAH->SetSkeletalMesh(CurrentSocialMediaChar->Male.FacialHair[SocialMediaFacialHairIndex]);
				FacialHairName = CurrentSocialMediaChar->Male.FacialHair[SocialMediaFacialHairIndex]->GetName();
			}

		}
		if(Global.gender==ECharGender::Female)
		{
			if(CurrentSocialMediaChar->Female.Hair.IsValidIndex(SocialMediaHairIndex))
			{
				HAI->SetSkeletalMesh(CurrentSocialMediaChar->Female.Hair[SocialMediaHairIndex]);
				HairName = CurrentSocialMediaChar->Female.Hair[SocialMediaHairIndex]->GetName();
			}
			else
			{
				SocialMediaHairIndex = CurrentSocialMediaChar->Female.Hair.Num()-1;
				HAI->SetSkeletalMesh(CurrentSocialMediaChar->Female.Hair[SocialMediaHairIndex]);
				HairName = CurrentSocialMediaChar->Female.Hair[SocialMediaHairIndex]->GetName();
			}

			if(CurrentSocialMediaChar->Female.FacialHair.IsValidIndex(SocialMediaFacialHairIndex))
			{
				FAH->SetSkeletalMesh(CurrentSocialMediaChar->Female.FacialHair[SocialMediaFacialHairIndex]);
				FacialHairName = CurrentSocialMediaChar->Female.FacialHair[SocialMediaFacialHairIndex]->GetName();
			}
			else
			{
				// SocialMediaHairIndex = CurrentSocialMediaChar->Female.FacialHair.Num()-1;
				// FAH->SetSkeletalMesh(CurrentSocialMediaChar->Female.FacialHair[SocialMediaFacialHairIndex]);
				// FacialHairName = CurrentSocialMediaChar->Female.FacialHair[SocialMediaFacialHairIndex]->GetName();
				FAH->SetSkeletalMesh(nullptr);
			}

		}
	}

	FString HairID = "";
	FString FacialHairID = "";

	if (HairName.Split(TEXT("_"), nullptr, &HairID))
	{
		HairID = HairID + "_001_001";
		const TMap<EBodyPart, UDataTable*>& BodyPartPDATables =
	(Global.gender == ECharGender::Male)
		? EditorDefaults->BodyPartPDATablesMale
		: EditorDefaults->BodyPartPDATablesFemale;
		UDataTable* const* TablePtr = BodyPartPDATables.Find(EBodyPart::HAI);
		if (TablePtr && *TablePtr)
		{
			UDataTable* HairDataTable = *TablePtr;

			// Now try to find a row named HairID in that DataTable
			FDataLookup* FoundRow = HairDataTable->FindRow<FDataLookup>(
				FName(*HairID),
				TEXT("UpdateSocialMediaHair")  // Context string for debugging
			);

			if(FoundRow)
			{
				UUnseenAssetData* PDA = Cast<UUnseenAssetData>(FoundRow->DataAsset);

				if (PDA)
				{
					HAI->UpdateMaterialFromPDA(PDA, Global.HairColorPreset, EditorDefaults->FacialFeaturesMaterial, true);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("PDA is Null"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Row is Null"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Table"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Split"));
	}

	if (FacialHairName.Split(TEXT("_"), nullptr, &FacialHairID))
	{
		FacialHairID = FacialHairID + "_001_001";
		const TMap<EBodyPart, UDataTable*>& BodyPartPDATables =
	(Global.gender == ECharGender::Male)
		? EditorDefaults->BodyPartPDATablesMale
		: EditorDefaults->BodyPartPDATablesFemale;
		UDataTable* const* TablePtr = BodyPartPDATables.Find(EBodyPart::FAH);
		if (TablePtr && *TablePtr)
		{
			UDataTable* FacialHairDataTable = *TablePtr;

			FDataLookup* FoundRow = FacialHairDataTable->FindRow<FDataLookup>(
				FName(*FacialHairID),
				TEXT("UpdateSocialMediaHair")  // Context string for debugging
			);
			if(FoundRow)
			{
				UUnseenAssetData* PDA = Cast<UUnseenAssetData>(FoundRow->DataAsset);

				if (PDA)
				{
					FAH->UpdateMaterialFromPDA(PDA, Global.HairColorPreset, EditorDefaults->FacialFeaturesMaterial, true);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("PDA is Null"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Row is Null"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Table"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Split"));
	}
}
void AUnseenCharacter::UpdateSocialMediaMaterials()
{
	if(SocialMediaEyeMatInstance)
	{BOD->SetMaterial(3, SocialMediaEyeMatInstance);}
	if(SocialMediaEyebrowsMatInstance)
	{BOD->SetMaterial(2, SocialMediaEyebrowsMatInstance);}
	if(SocialMediaFaceMatInstance)
	{BOD->SetMaterial(0, SocialMediaFaceMatInstance);}
	if(SocialMediaEyelashMatInstance)
	{BOD->SetMaterial(6, SocialMediaEyeMatInstance);}
	if(SocialMediaTongueMatInstance)
	{BOD->SetMaterial(4, SocialMediaEyebrowsMatInstance);}
	if(SocialMediaTeethMatInstance)
	{BOD->SetMaterial(5, SocialMediaFaceMatInstance);}
	
	
	if(SocialMediaBodyMatInstance)
	{
		UUnseenAssetData* CLUData = *CurrentCharacter.Find(EBodyPart::CLL);
		UUnseenAssetData* CLLData = *CurrentCharacter.Find(EBodyPart::CLU);
		UUnseenAssetData* SHOData = *CurrentCharacter.Find(EBodyPart::SHO);
		UMaterialInstanceDynamic* DynMatInstance = UMaterialInstanceDynamic::Create(SocialMediaBodyMatInstance, this);
		if(CLUData && CLUData->Texture)
		{
			DynMatInstance->SetTextureParameterValue("CLU", CLUData->Texture);
			UE_LOG(LogTemp, Warning, TEXT("Data and Texture available for %s"), *CLUData->Texture->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Data or Texture unavailable for CLU"));
		}
		if(CLLData && CLLData->Texture)
		{
			DynMatInstance->SetTextureParameterValue("CLL", CLLData->Texture);
			UE_LOG(LogTemp, Warning, TEXT("Data and Texture available for CLL"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Data or Texture unavailable for CLL"));
		}
		if(SHOData && SHOData->Texture)
		{
			DynMatInstance->SetTextureParameterValue("SHO", SHOData->Texture);
			UE_LOG(LogTemp, Warning, TEXT("Data and Texture available for SHO"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Data or Texture unavailable for SHO"));
		}
		BOD->SetMaterial(1, DynMatInstance);
	}
}

void AUnseenCharacter::AddUnderwearToData()
{
}

//---------------------------------JSON Operations----------------------//
FUnseenWearablesDataRef AUnseenCharacter:: GetFaceBodyTextures(ECharGender Gender, const FString& RowName, bool IsBody)
{
	// Determine the correct DataTable based on gender
	UDataTable* DataTable = nullptr;
    if(IsBody)
    {
	    if (Gender == ECharGender::Male)
	    {
	    	DataTable = *EditorDefaults->GenderBodyTables.Find(ECharGender::Male);
	    }
	    else if (Gender == ECharGender::Female)
	    {
	    	DataTable = *EditorDefaults->GenderBodyTables.Find(ECharGender::Female);
	    }
    }
    else
    {
    	if (Gender == ECharGender::Male)
    	{
    		DataTable = *EditorDefaults->GenderFaceTables.Find(ECharGender::Male);
    	}
    	else if (Gender == ECharGender::Female)
    	{
    		DataTable = *EditorDefaults->GenderFaceTables.Find(ECharGender::Female);
    	}
    }

	// Validate the DataTable
	if (!DataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Found"));
		return FUnseenWearablesDataRef(); // Return default struct if DataTable is null
	}

	// Fetch the row from the DataTable
	FUnseenWearablesDataRef* WearableData = DataTable->FindRow<FUnseenWearablesDataRef>(*RowName, TEXT("GetWearableDataFromTable"));

	if (!WearableData)
	{
		UE_LOG(LogTemp, Error, TEXT("Row %s not found in DataTable"), *RowName);
		return FUnseenWearablesDataRef(); // Return default struct if row is not found
	}

	return *WearableData; // Return the found row
}

void AUnseenCharacter::ExportPdaCollections()
{
	UJsonHandler* JsonHandler = NewObject<UJsonHandler>();
	TArray<FName> RowNames = EditorDefaults->Collections->GetRowNames();

	for(FName RowName : RowNames)
	{
		TArray<FUnseenWearablesDataRef> CollectionNFts = EditorDefaults->GetAndConvertCollectionToDataRefFromIndex(RowName);
		for(FUnseenWearablesDataRef CollectionNftSingle : CollectionNFts)
		{
			FUnseenWearablesData AssetData = EditorDefaults->ConvertAssetInfoRefToData(CollectionNftSingle);
			JsonHandler->WriteAssetJSONRefToFile("", CollectionNftSingle.wearable_id, AssetData, CollectionNftSingle.bodyPart,CollectionNftSingle.materialType);
		}
	}
}

void AUnseenCharacter::ExportPdaCollectionsMarketplace()
{
	UJsonHandler* JsonHandler = NewObject<UJsonHandler>();
	TArray<FName> RowNames = EditorDefaults->Collections->GetRowNames();
	int Counter = 1;
	int RarityCount = 1;
	for(FName RowName : RowNames)
	{
		TArray<FUnseenWearablesDataRef> CollectionNFts = EditorDefaults->GetAndConvertCollectionToDataRefFromIndex(RowName);
		for(FUnseenWearablesDataRef CollectionNftSingle : CollectionNFts)
		{
			if(ExportCollectionsWithRarity && CollectionNftSingle.bodyPart!=EBodyPart::AEY && CollectionNftSingle.bodyPart!=EBodyPart::AHD)
			{
				RarityCount = 5;
			}
			else
			{
				RarityCount = 1;
			}
			for(int32 i = 0; i<RarityCount; i++)
			{
				FUnseenWearablesData AssetData = EditorDefaults->ConvertAssetInfoRefToData(CollectionNftSingle);
				JsonHandler->WriteAssetJSONRefToFile("", FString::Printf(TEXT("%d"), Counter) + " - " + CollectionNftSingle.wearable_id, AssetData, CollectionNftSingle.bodyPart,CollectionNftSingle.materialType);
				Counter++;
			}
		}
	}
}


