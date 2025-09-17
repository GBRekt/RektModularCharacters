// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "Engine/DataAsset.h"
#include "UnseenSocialMediaCharData.generated.h"

/**
 * 
 */
UCLASS()
class UNSEENMODULARCHARACTERS_API UUnseenSocialMediaCharData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	FSocialMediaCharInfo Male;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	FSocialMediaCharInfo Female;	
};
