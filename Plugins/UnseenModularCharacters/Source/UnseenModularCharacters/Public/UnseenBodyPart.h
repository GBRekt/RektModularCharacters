// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameTypes.h"
#include "Components/SkeletalMeshComponent.h"
#include "UnseenBodyPart.generated.h"

/**
 * 
 */
UCLASS()
class UNSEENMODULARCHARACTERS_API UUnseenBodyPart : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Materials")
	UMaterialInstanceDynamic* MaterialInstance = nullptr;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	EBodyPart BodyPart;	
	
	UFUNCTION(BlueprintCallable, Category = "Morph Targets")
	void UpdateMorphTargets (TArray<FName> MorphTargets);

	UFUNCTION(BlueprintCallable, Category = "Asset Update")
	void UpdateFromAssetInfo(FUnseenWearablesDataRef AssetInfo, UMaterial* Material);

	UFUNCTION(BlueprintCallable, Category = "Asset Update")
	void UpdateFromPDA(UUnseenAssetData* PDA, UUnseenColorPresetData* ColorPreset, UMaterial* Material, bool IsSocialMedia);
	void UpdateMaterialFromPDA(UUnseenAssetData* PDA, UUnseenColorPresetData* ColorPreset, UMaterial* Material,
	                           bool IsSocialMedia);

	UFUNCTION(BlueprintCallable, Category = "Asset Update")
	void ClearMesh();
	
};
