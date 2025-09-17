// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "Engine/DataAsset.h"
#include "UnseenColorPresetData.generated.h"

/**
 * 
 */
UCLASS()
class UNSEENMODULARCHARACTERS_API UUnseenColorPresetData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int PresetIndex;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FUnseenCharacterColorLinear> IconColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FUnseenCharacterColorLinear> PresetColors;  
};
