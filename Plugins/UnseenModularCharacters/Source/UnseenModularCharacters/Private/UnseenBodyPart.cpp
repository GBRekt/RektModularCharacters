// Fill out your copyright notice in the Description page of Project Settings.


#include "UnseenBodyPart.h"

#include "UnseenAssetData.h"
#include "UnseenColorPresetData.h"
#include "Materials/MaterialInstanceDynamic.h"

void UUnseenBodyPart::UpdateMorphTargets(TArray<FName> MorphTargets)
{
	ClearMorphTargets();
	for(FName MorphTargetName : MorphTargets)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MorphTargetName.ToString());
		SetMorphTarget(MorphTargetName, 1.f);
	}
}

void UUnseenBodyPart::UpdateFromAssetInfo(FUnseenWearablesDataRef AssetInfo, UMaterial* Material)
{
	if(AssetInfo.mesh!=nullptr)
	{
		SetSkeletalMeshAsset(AssetInfo.mesh);
	}
	
	if(MaterialInstance == nullptr)
	{
		MaterialInstance = CreateDynamicMaterialInstance(0, Material);
	}
	
	 if(AssetInfo.texture!=nullptr)
	 {
	 	MaterialInstance->SetTextureParameterValue("Main", AssetInfo.texture);
	 }

	for(FUnseenCharacterColorLinear Color : AssetInfo.colors)
	{
		MaterialInstance->SetVectorParameterValue(FName(Color.Name), Color.Color);
	}
	for(FUnseenCharacterMaterialData MaterialValue : AssetInfo.materialValues)
	{
		MaterialInstance->SetScalarParameterValue(FName(MaterialValue.name + ".r"), MaterialValue.values.r);
		MaterialInstance->SetScalarParameterValue(FName(MaterialValue.name + ".g"), MaterialValue.values.g);
		MaterialInstance->SetScalarParameterValue(FName(MaterialValue.name + ".b"), MaterialValue.values.b);
	}
	if(AssetInfo.materialType == EUnseenMaterialType::Custom)
	{
		MaterialInstance->SetScalarParameterValue(FName("IsCustom"), 1.0);
	}
	else
	{
		MaterialInstance->SetScalarParameterValue(FName("IsCustom"), 0.0);
	}
	
	SetMaterial(0, MaterialInstance);	
}

void UUnseenBodyPart::UpdateFromPDA(UUnseenAssetData* PDA, UUnseenColorPresetData* ColorPreset, UMaterial* Material, bool IsSocialMedia)
{
	if(PDA)
	{
		if(PDA->GameMesh)
		{
			if(IsSocialMedia)
			{
				SetSkeletalMeshAsset(PDA->SocialMediaMesh);
			}
			else
			{
				SetSkeletalMeshAsset(PDA->GameMesh);
			}

		}
		
		if(MaterialInstance == nullptr)
		{
			MaterialInstance = CreateDynamicMaterialInstance(0, Material);
		}
		
		if(PDA->Texture!=nullptr)
		{
			MaterialInstance->SetTextureParameterValue("Main", PDA->Texture);
		}
		TArray<FUnseenCharacterColorLinear> AssetColors;
		TArray<FUnseenCharacterMaterialData> AssetMaterialValues;

		if(ColorPreset)
		{
			AssetColors = ColorPreset->PresetColors;
		}
		else
		{
			AssetColors = PDA->Colors;
		}
		
		for(FUnseenCharacterColorLinear Color : AssetColors)
		{
			MaterialInstance->SetVectorParameterValue(FName(Color.Name), Color.Color);
		}
		for(FUnseenCharacterMaterialData MaterialValue : PDA->MaterialValues)
		{
			MaterialInstance->SetScalarParameterValue(FName(MaterialValue.name + ".r"), MaterialValue.values.r);
			MaterialInstance->SetScalarParameterValue(FName(MaterialValue.name + ".g"), MaterialValue.values.g);
			MaterialInstance->SetScalarParameterValue(FName(MaterialValue.name + ".b"), MaterialValue.values.b);
		}

		if(PDA->MaterialType == EUnseenMaterialType::Custom)
		{
			MaterialInstance->SetScalarParameterValue(FName("IsCustom"), 1.0);
		}
		else
		{
			MaterialInstance->SetScalarParameterValue(FName("IsCustom"), 0.0);
		}
		
		SetMaterial(0, MaterialInstance);
	}
}

void UUnseenBodyPart::UpdateMaterialFromPDA(UUnseenAssetData* PDA, UUnseenColorPresetData* ColorPreset, UMaterial* Material, bool IsSocialMedia)
{
	if(PDA)
	{
	
		if(MaterialInstance == nullptr)
		{
			MaterialInstance = CreateDynamicMaterialInstance(0, Material);
		}
		
		if(PDA->Texture!=nullptr)
		{
			MaterialInstance->SetTextureParameterValue("Main", PDA->Texture);
		}
		TArray<FUnseenCharacterColorLinear> AssetColors;
		TArray<FUnseenCharacterMaterialData> AssetMaterialValues;

		if(ColorPreset)
		{
			AssetColors = ColorPreset->PresetColors;
		}
		else
		{
			AssetColors = PDA->Colors;
		}
		
		for(FUnseenCharacterColorLinear Color : AssetColors)
		{
			MaterialInstance->SetVectorParameterValue(FName(Color.Name), Color.Color);
		}
		for(FUnseenCharacterMaterialData MaterialValue : PDA->MaterialValues)
		{
			MaterialInstance->SetScalarParameterValue(FName(MaterialValue.name + ".r"), MaterialValue.values.r);
			MaterialInstance->SetScalarParameterValue(FName(MaterialValue.name + ".g"), MaterialValue.values.g);
			MaterialInstance->SetScalarParameterValue(FName(MaterialValue.name + ".b"), MaterialValue.values.b);
		}
		
		SetMaterial(0, MaterialInstance);
	}
}


void UUnseenBodyPart::ClearMesh()
{
	SetSkeletalMesh(nullptr);
}
