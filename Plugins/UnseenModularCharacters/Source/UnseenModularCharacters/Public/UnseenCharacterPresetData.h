// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "Engine/DataAsset.h"
#include "UnseenCharacterPresetData.generated.h"

class UUnseenCollectionData;
/**
 * 
 */
UCLASS()
class UNSEENMODULARCHARACTERS_API UUnseenCharacterPresetData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	FUnseenPresetGlobalData Global;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	TMap<EBodyPart, FBodyPartDataInfo> BodyPartData;
	
};
