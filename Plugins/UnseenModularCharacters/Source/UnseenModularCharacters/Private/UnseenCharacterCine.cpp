// Fill out your copyright notice in the Description page of Project Settings.


#include "UnseenCharacterCine.h"
#include "UnseenBodyPartCine.h"

class UUnseenBodyPartCine;

// Sets default values
AUnseenCharacterCine::AUnseenCharacterCine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<USceneComponent>("Root");
	
	AHD = CreateDefaultSubobject<UUnseenBodyPartCine>("Headgear");
	AHD->SetupAttachment(Root);
	AEY = CreateDefaultSubobject<UUnseenBodyPartCine>("Glasses");
	AEY->SetupAttachment(Root);
	SHO = CreateDefaultSubobject<UUnseenBodyPartCine>("Shoes");
	SHO->SetupAttachment(Root);
	CLL = CreateDefaultSubobject<UUnseenBodyPartCine>("Pants");
	CLL->SetupAttachment(Root);
	CLU = CreateDefaultSubobject<UUnseenBodyPartCine>("Shirt");
	CLU->SetupAttachment(Root);
	HAI = CreateDefaultSubobject<UUnseenBodyPartCine>("Hair");
	HAI->SetupAttachment(Root);
	FAH = CreateDefaultSubobject<UUnseenBodyPartCine>("Facial Hair");
	FAH->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AUnseenCharacterCine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnseenCharacterCine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

