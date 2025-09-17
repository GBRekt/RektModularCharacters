// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorDefaults.h"
#include "UnseenBodyPart.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameTypes.h"
#include "UnseenCharacter.generated.h"

class UBattlePassData;
class UUnseenCharacterPresetData;
class UUnseenCollectionData;
class UEditorDefaults;

UCLASS()
class UNSEENMODULARCHARACTERS_API AUnseenCharacter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnseenCharacter();
#pragma region Components
	// UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	// USceneComponent* Root;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	USkeletalMeshComponent* SkeletalDriver;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPart* BOD;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPart* EYE;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPart* HAI;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Unseen | Components")
	UUnseenBodyPart* EYB;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Unseen | Components")
	UUnseenBodyPart* FAH;	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Unseen | Components")
	UUnseenBodyPart* CLL;	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Unseen | Components")
	UUnseenBodyPart* CLU;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPart* SHO;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPart* AEY;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPart* AHD;
#pragma endregion
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen | Components")
	UEditorDefaults* EditorDefaults;
	UPROPERTY(BlueprintReadWrite,  Category = "Unseen | Components")
	int32 DefaultsColorPresetIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Master")
	UUnseenCharacterPresetData* MasterPreset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Master")
	bool LoadFromMasterPreset;
	UPROPERTY(VisibleAnywhere, Category = "Modular Characters Master")
	FUnseenPresetGlobalData MasterGlobal;
	UPROPERTY(VisibleAnywhere, Category = "Modular Characters Master")
	TMap<EBodyPart, FBodyPartDataInfo> MasterBodyPartData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	bool IsSocialMedia;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	int SocialMediaHairIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	int SocialMediaFacialHairIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	UUnseenSocialMediaCharData* CurrentSocialMediaChar;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	UMaterialInstance* SocialMediaBodyMatInstance = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	UMaterialInstance* SocialMediaFaceMatInstance = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	UMaterialInstance* SocialMediaEyeMatInstance = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	UMaterialInstance* SocialMediaEyebrowsMatInstance = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	UMaterialInstance* SocialMediaEyelashMatInstance = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	UMaterialInstance* SocialMediaTeethMatInstance = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters Social Media")
	UMaterialInstance* SocialMediaTongueMatInstance = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters")
	FUnseenPresetGlobalData Global;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters")
	TMap<EBodyPart, FBodyPartDataInfo> BodyPartData;
	UPROPERTY(BlueprintReadWrite, Category = "Modular Characters")
	int CategoryResultCount = 150;
	UPROPERTY(BlueprintReadWrite, Category = "Modular Characters")
	UMaterialInstanceDynamic* BodyMaterial = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "Materials")
	UMaterialInstanceDynamic* FaceMaterial = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "Defaults")
	TArray<UUnseenBodyPart*> BodyPartsArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters JSON")
	bool ExportCollectionsWithRarity = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters JSON")
	EBodyPart OperationBodyPart;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters JSON")
	TMap<EBodyPart, UUnseenAssetData*> CurrentCharacter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters JSON")
	TArray<FItemRarity> StoreItems;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modular Characters JSON")
	UBattlePassData* BattlePass;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//-------------------PERMUTATIONS----------------------------------//
	TArray<FPermutationIndices> SplitShuffleChopResults(TArray<FPermutationIndices> Permutations);
	TArray<FUnseenWearablesDataRef> GenerateDefaultsPda(int32 ColorIndex);


	//----------------------Helpers----------------------------//
	UFUNCTION(BlueprintCallable, Category = "Customization")
	UUnseenAssetData* PickDataAsset(EBodyPart BodyPart);
	UFUNCTION(BlueprintCallable, Category = "Customization")
	UUnseenColorPresetData* PickColorPdaPreset(EBodyPart BodyPart);
	UFUNCTION(BlueprintCallable, Category = "Assets Update")
	UUnseenBodyPart* ReturnBodyPart(EBodyPart BodyPart);
	UFUNCTION(BlueprintCallable, Category = "Assets Update")
	FUnseenCharacterMetaDataRef ConvertIndicesToPda(FPermutationIndices CharacterIndices);

	//------------------------Character Updaters------------------------//
	UFUNCTION(BlueprintCallable, Category = "Assets Update")
	void UpdateBodyPartsFromPDA();
	UFUNCTION(BlueprintCallable, Category = "Assets Update")
	void UpdateSkinMasks(UUnseenAssetData* AssetData, bool IsActive);
	UFUNCTION(BlueprintCallable, Category = "Assets Update")
	void UpdateSkin();
	UFUNCTION(BlueprintCallable, Category = "Morph Targets")
	void UpdateComponentsMorphTargets();
	UFUNCTION(BlueprintCallable, Category = "Assets Update")
	void UpdateBody();
	UFUNCTION(BlueprintCallable, Category = "Assets Update")
	void UpdateSocialMediaHair();
	UFUNCTION(BlueprintCallable, Category = "Assets Update")
	void UpdateSocialMediaMaterials();
	UFUNCTION(BlueprintCallable, Category = "Assets Update")
	void AddUnderwearToData(); 
	
	//---------------------------------JSON Operations----------------------//

	FUnseenWearablesDataRef GetFaceBodyTextures(ECharGender Gender, const FString& RowName, bool IsBody);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void ExportPdaCollections();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Modular Characters")
	void ExportPdaCollectionsMarketplace();

	
	
	//---------------------------------Old Code--------------------------------------------//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen | Character Customization | Global")
	FUnseenCharacterGlobalDataRef GlobalData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen | Character Customization | Colors")
	FLinearColor SkinTone = FLinearColor(1.f, 0.5f, 0.32f, 1.f);
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Unseen | Character Customization | Reference Data")
	TMap<EBodyPart, FUnseenWearablesDataRef> CurrentAssetsInfo;

};
