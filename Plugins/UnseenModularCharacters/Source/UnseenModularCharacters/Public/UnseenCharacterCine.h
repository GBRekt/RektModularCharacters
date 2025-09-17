// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "GameFramework/Actor.h"
#include "UnseenCharacterCine.generated.h"

class UUnseenBodyPartCine;

UCLASS()
class UNSEENMODULARCHARACTERS_API AUnseenCharacterCine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnseenCharacterCine();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	USceneComponent* Root;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPartCine* Character;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPartCine* HAI;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Unseen | Components")
	UUnseenBodyPartCine* FAH;	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Unseen | Components")
	UUnseenBodyPartCine* CLL;	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Unseen | Components")
	UUnseenBodyPartCine* CLU;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPartCine* SHO;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPartCine* AEY;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Unseen | Components")
	UUnseenBodyPartCine* AHD;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unseen | Customization")
	FUnseenCharacterGlobalDataRef GlobalData;

};
