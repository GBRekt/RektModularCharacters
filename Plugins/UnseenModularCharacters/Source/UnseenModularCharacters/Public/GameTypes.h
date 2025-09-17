#pragma once

#include "Engine/DataTable.h"
#include "Materials/Material.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Texture.h"
#include "GameTypes.generated.h"

class UUnseenColorPresetData;
class UUnseenAssetData;
class UUnseenCollectionData;
class UPrimaryDataAsset;

UENUM(BlueprintType)
enum class ECharGender : uint8 {Male, Female, None};

UENUM(BlueprintType)
enum class EBodyType : uint8 {Skinny, Muscular, Overweight};

UENUM(BlueprintType)
enum class EPersonalities : uint8 {NoCoiner, DayTrader, Hodler, Zoomer, Influencer, Boomer, Hacker, RobotDefault};

UENUM(BlueprintType)
enum class EBodyPart : uint8 {BOD, FAC, CLU, CLL, SHO, AEY, AHD, HAI, EYB, EYE, FAH, ROB};

UENUM(BlueprintType)
enum class EUnseenMaterialType : uint8 {Wearables, FacialFeatures, Skin, Robot, Custom};

UENUM(BlueprintType)
enum class EOverrideMode : uint8 {Custom, Collection, Master};

UENUM(BlueprintType)
enum class ERarity : uint8 {Common, Uncommon, Rare, Epic, Legendary, None};

USTRUCT(Blueprintable)
struct FDataLookup : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	UPrimaryDataAsset* DataAsset;
	
};

USTRUCT(Blueprintable)
struct FColorPresetDataLookup : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	UUnseenColorPresetData* DataAsset;
	
};


USTRUCT(Blueprintable)
struct FCollectionDataLookup : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	UUnseenCollectionData* DataAsset;	
};

USTRUCT(Blueprintable)
struct FSocialMediaCharInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	USkeletalMesh* Body;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	TArray<USkeletalMesh*> Hair;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	TArray<USkeletalMesh*> FacialHair;
	
	
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenColorData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	int32 r = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	int32 g = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	int32 b = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	int32 a = 0;

	FUnseenColorData()
	: r(0), g(0), b(0), a(0) 
	{
	}

	FColor BaseToToFColor() const
	{
		return FColor(r, g,b, a);
	}

	FVector4 ToFVector4() const
	{
		return FVector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}

	FVector ToFVector3() const
	{
		return FVector(r / 255.0f, g / 255.0f, b / 255.0f);
	}
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FMaterialValues
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	float r = 0.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	float g = 0.0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	float b = 0.0;
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenCharacterColor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	FString name = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	FUnseenColorData colorData;
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenCharacterColorLinear : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	FString Name = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	FLinearColor Color;
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenLinearColorArray : public FTableRowBase
{
	GENERATED_BODY()

	TArray<FUnseenCharacterColorLinear> ColorPreset;
	
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenCharacterMaterialData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	FString name = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	FMaterialValues values;	
};


USTRUCT(Blueprintable)
struct FItemRarity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Drop Data")
	UUnseenAssetData* Asset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Drop Data")
	TSet<ERarity> Rarities; 
	
};

USTRUCT(Blueprintable)
struct FCollectionRarity
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Drop Data")
	UUnseenCollectionData* Asset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Drop Data")
	TArray<ERarity> Rarities; 
	
};

USTRUCT(Blueprintable)
struct FBodyPartIndex
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int32 Index = 1;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Unseen Character Assets")
	FName Row;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int32 ColorPresetIndex = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	bool Override = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	EOverrideMode OverridenMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	bool Active = true;
	
};

USTRUCT(Blueprintable)
struct FBodyPartDataInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	UUnseenAssetData* Data = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	bool OverrideAsset = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	EOverrideMode OverrideMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	UUnseenColorPresetData* ColorPreset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	bool OverrideColorPreset = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	bool Active = true;	
};

USTRUCT(BlueprintType)
struct FPublicMetadataAttributes
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FString trait_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FString Value;

};

USTRUCT(BlueprintType)
struct FPublicMetadata
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FString Name = "The Generates #";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FString Description = "The world was ready, but the inhabitants were still missing. REKT's intention was to draw out the rejects and lunatics that make up the web3 space, and use them as lab rats for further studies. So, it generated a bunch of degenerates to encourage its audience out of hiding, giving shape to The Generates.";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FString Image = "https://dev.assets.rektgames.io/thegenerates/assets/images/";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int Season = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FPublicMetadataAttributes> Attributes = {};

};

USTRUCT(Blueprintable)
struct FUnseenColorPresetLinear : public FTableRowBase
{
	GENERATED_BODY()

	FUnseenColorPresetLinear() 
		: PresetIndex(0) // Initialize members
	{}


	FUnseenColorPresetLinear(int InPresetIndex, const TArray<FUnseenCharacterColorLinear>& InIconColors, const TArray<FUnseenCharacterColorLinear>& InPresetColors)
		: PresetIndex(InPresetIndex), IconColors(InIconColors), PresetColors(InPresetColors)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int PresetIndex = 0;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FUnseenCharacterColorLinear> IconColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FUnseenCharacterColorLinear> PresetColors;    
};

USTRUCT(Blueprintable)
struct FUnseenColorPreset : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int PresetIndex;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FUnseenCharacterColor> IconColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FUnseenCharacterColor> PresetColors;    
};

USTRUCT(Blueprintable)
struct FNftIdInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Characters | Global")
	EBodyPart BodyPart = EBodyPart::BOD;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Characters | Global")
	int32 BodyPartMeshID = 1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Characters | Global")
	int32 BodyPartTextureID = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Characters | Global")
	int32 BodyPartColorID = 1;

	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Characters | Global")
	// bool HasBodyPartColorID = false;
};

USTRUCT(Blueprintable)
struct FUnseenCollectionInfo : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	TArray<FNftIdInfo> Nfts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	int StartingID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	bool Released = false;    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FName BodyMorphTarget = "BODSM";

	FUnseenCollectionInfo()
	{
		Nfts = {{EBodyPart::CLU, 1,1,1},
			{EBodyPart::CLL, 1, 1, 1},
			{EBodyPart::SHO, 1, 1, 1},
			{EBodyPart::AEY, 1, 1, 1}};
	}
};

USTRUCT(Blueprintable)
struct FUnseenCollectionPda : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	TArray<UUnseenAssetData*> Nfts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	int StartingID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release Info")
	bool Released = false;    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FName BodyMorphTarget = "BODSM";

};

USTRUCT(BlueprintType)
struct FPermutationIndices
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int Gender = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int BodyType = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int Personality = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int Hair = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int Eyes = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int Eyebrows = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int FacialHair = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int SkinTone = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int HairColor = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int EyeColor = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int OnesieColor = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	int ShoeColor = 1;
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenWearablesData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString wearable_id = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString collection_id = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	int colorPresetIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	bool isTranslucent = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString materialType = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString bodyPart = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	bool bIsBodyTypeTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString mesh = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString texture = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenCharacterColor> colors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenCharacterMaterialData> materialValues;	
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenWearablesDataRef : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString wearable_id = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString collection_id = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	int colorPresetIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	EUnseenMaterialType materialType = EUnseenMaterialType::Wearables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	EBodyPart bodyPart = EBodyPart::BOD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	bool bIsBodyTypeTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	USkeletalMesh* mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	UTexture* texture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenCharacterColorLinear> colors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenCharacterMaterialData> materialValues;	
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenCharacterTexture
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Unseen Character")
	FString name;

	UPROPERTY(BlueprintReadOnly, Category = "Unseen Character")
	FString paramName;

	UPROPERTY(BlueprintReadOnly, Category = "Unseen Character")
	FString textureName;
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenCharacterTextureRef
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Unseen Character")
	FString name;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Unseen Character")
	FString paramName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Unseen Character")
	UTexture* texture;
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenCharacterGlobalData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString bodyType = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString personality = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString gender = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString bodyMesh = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FString MaterialType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FUnseenColorData skinTone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenCharacterTexture> textures;	
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenCharacterGlobalDataRef
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	EBodyType bodyType = EBodyType::Skinny;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	EPersonalities personality = EPersonalities::DayTrader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	ECharGender gender = ECharGender::Male;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	USkeletalMesh* bodyMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	EUnseenMaterialType MaterialType = EUnseenMaterialType::Skin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FLinearColor skinTone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenCharacterTextureRef> textures;	
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenPresetGlobalData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	EBodyType bodyType = EBodyType::Skinny;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	EPersonalities personality = EPersonalities::DayTrader;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	ECharGender gender = ECharGender::Male;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FLinearColor skinTone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	bool IsRobot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	UUnseenCollectionData* CollectionData = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen Character")
	bool LoadFromCollection = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	UUnseenColorPresetData* HairColorPreset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	UUnseenColorPresetData* EyeColorPreset;
	
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenCharacterMetaData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FUnseenCharacterGlobalData globalData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenWearablesData> wearables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<int32> wearable_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenWearablesData> default_wearables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenWearablesData> customizableData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenWearablesData> underwear;
};

USTRUCT(BlueprintType, Category = "Unseen Character")
struct FUnseenCharacterMetaDataRef
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	FUnseenCharacterGlobalDataRef globalData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenWearablesDataRef> wearables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<int32> wearable_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenWearablesDataRef> default_wearables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenWearablesDataRef> customizableData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character")
	TArray<FUnseenWearablesDataRef> underwear;
};

// Social Media Specific //

USTRUCT(Blueprintable)
struct FSocialMediaTableData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen | Attributes")
	USkeletalMesh* MainSkeletalMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen | Attributes")
	USkeletalMesh* HairSkeletalMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen | Attributes")
	USkeletalMesh* FacialHairSkeletalMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen | Attributes")
	FLinearColor SkinTone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen | Attributes")
	float HueShift;


};

USTRUCT(Blueprintable)
struct FUnseenStoreMetaData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FString description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	FString image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<FPublicMetadataAttributes> Attributes = {};
	
	
};

USTRUCT(Blueprintable)
struct FChests
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unseen Character Assets")
	TArray<UUnseenAssetData*> ChestItems;
	
};

class GameTypes
{
public:
	
};
