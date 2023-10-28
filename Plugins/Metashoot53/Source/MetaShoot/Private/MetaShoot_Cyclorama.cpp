// Copyright 2023, VINZI Studio S.L. All rights reserved


#include "MetaShoot_Cyclorama.h"

#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Components/DecalComponent.h"

// Sets default values
AMetaShoot_Cyclorama::AMetaShoot_Cyclorama()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cyclorama_Root = CreateDefaultSubobject<USceneComponent>(FName("Cyclorama Root"));
	this->SetRootComponent(Cyclorama_Root);

	Cyclorama_C = CreateDefaultSubobject<UStaticMeshComponent>(FName("Cyclorama C"));
	Cyclorama_C->SetupAttachment(Cyclorama_Root);
	Cyclorama_C->SetRelativeLocation(FVector(-XOffset, 0.0f, -0.5f));
	
	Cyclorama_R = CreateDefaultSubobject<UStaticMeshComponent>(FName("Cyclorama R"));
	Cyclorama_R->SetupAttachment(Cyclorama_Root);

	Cyclorama_L = CreateDefaultSubobject<UStaticMeshComponent>(FName("Cyclorama L"));
	Cyclorama_L->SetupAttachment(Cyclorama_Root);


	UEnclosure = CreateDefaultSubobject<UStaticMeshComponent>(FName("Enclosure"));
	UEnclosure->SetupAttachment(Cyclorama_Root);
	UEnclosure->SetRelativeLocation(FVector(-XOffset, 0.0f, 0.0f));


	Cyclorama_Frame00 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Frame00"));
	Cyclorama_Frame00->SetupAttachment(Cyclorama_L);
	Cyclorama_Frame00->SetRelativeLocation(FVector(-40.0f, 0.0f, 0.0f));

	Cyclorama_Frame01 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Frame01"));
	Cyclorama_Frame01->SetupAttachment(Cyclorama_L);
	Cyclorama_Frame01->SetRelativeLocation(FVector(120.0, 0.0f, 0.0f));

	Cyclorama_Frame02 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Frame02"));
	Cyclorama_Frame02->SetupAttachment(Cyclorama_L);
	Cyclorama_Frame02->SetRelativeLocation(FVector(280.0f, 0.0f, 0.0f));

	Cyclorama_Frame03 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Frame03"));
	Cyclorama_Frame03->SetupAttachment(Cyclorama_L);
	Cyclorama_Frame03->SetRelativeLocation(FVector(440.0f, 0.0f, 0.0f));


	Cyclorama_Frame04 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Frame04"));
	Cyclorama_Frame04->SetupAttachment(Cyclorama_R);
	Cyclorama_Frame04->SetRelativeLocation(FVector(-40.0f, 0.0f, 0.0f));
	Cyclorama_Frame04->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	Cyclorama_Frame05 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Frame05"));
	Cyclorama_Frame05->SetupAttachment(Cyclorama_R);
	Cyclorama_Frame05->SetRelativeLocation(FVector(120.0, 0.0f, 0.0f));
	Cyclorama_Frame05->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	Cyclorama_Frame06 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Frame06"));
	Cyclorama_Frame06->SetupAttachment(Cyclorama_R);
	Cyclorama_Frame06->SetRelativeLocation(FVector(280.0f, 0.0f, 0.0f));
	Cyclorama_Frame06->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	Cyclorama_Frame07 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Frame07"));
	Cyclorama_Frame07->SetupAttachment(Cyclorama_R);
	Cyclorama_Frame07->SetRelativeLocation(FVector(440.0f, 0.0f, 0.0f));
	Cyclorama_Frame07->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	Cyclorama_FrameBack01 = CreateDefaultSubobject<UStaticMeshComponent>(FName("FrameBackN01"));
	Cyclorama_FrameBack02 = CreateDefaultSubobject<UStaticMeshComponent>(FName("FrameBackN02"));
	Cyclorama_FrameBack03 = CreateDefaultSubobject<UStaticMeshComponent>(FName("FrameBackN03"));
	Cyclorama_FrameBack04 = CreateDefaultSubobject<UStaticMeshComponent>(FName("FrameBackN04"));
	Cyclorama_FrameBack05 = CreateDefaultSubobject<UStaticMeshComponent>(FName("FrameBackN05"));
	Cyclorama_FrameBack06 = CreateDefaultSubobject<UStaticMeshComponent>(FName("FrameBackN06"));

	Cyclorama_FrameBack01->SetupAttachment(Cyclorama_Root);
	Cyclorama_FrameBack02->SetupAttachment(Cyclorama_Root);
	Cyclorama_FrameBack03->SetupAttachment(Cyclorama_Root);
	Cyclorama_FrameBack04->SetupAttachment(Cyclorama_Root);
	Cyclorama_FrameBack05->SetupAttachment(Cyclorama_Root);
	Cyclorama_FrameBack06->SetupAttachment(Cyclorama_Root);

	SkirtingBoard01 = CreateDefaultSubobject<UStaticMeshComponent>(FName("SkirtingBoard_C"));
	SkirtingBoard01->SetupAttachment(Cyclorama_C);

	SkirtingBoard02 = CreateDefaultSubobject<UStaticMeshComponent>(FName("SkirtingBoard_R"));
	SkirtingBoard02->SetupAttachment(Cyclorama_R);

	SkirtingBoard03 = CreateDefaultSubobject<UStaticMeshComponent>(FName("SkirtingBoard_L"));
	SkirtingBoard03->SetupAttachment(Cyclorama_L);

	Cyclorama_Fog = CreateDefaultSubobject<UExponentialHeightFogComponent>(FName("Fog"));
	Cyclorama_Fog->SetupAttachment(Cyclorama_Root);
	Cyclorama_Fog->SetVolumetricFog(true);


	/*Cyclorama_Frame->AddInstance(FTransform ( FRotator(0.0f, 0.0f, 0.0f), FVector(-40.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f) ) );
	Cyclorama_Frame->AddInstance(FTransform ( FRotator(0.0f, 0.0f, 0.0f), FVector(120.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f) ) );
	Cyclorama_Frame->AddInstance(FTransform ( FRotator(0.0f, 0.0f, 0.0f), FVector(280.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f) ) );
	Cyclorama_Frame->AddInstance(FTransform ( FRotator(0.0f, 0.0f, 0.0f), FVector(440.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f) ) );*/

	//Cyclorama_Decal = CreateDefaultSubobject<UDecalComponent>(FName("Decal"));
	//Cyclorama_Decal->SetupAttachment(Cyclorama_C);

	//Cyclorama_Fog = CreateDefaultSubobject<UExponentialHeightFogComponent>(FName("Fog"));
	//Cyclorama_Fog->SetupAttachment(Cyclorama_C);




	//Make old structure version work

	/*if (VColorC == FLinearColor::Transparent)
	{
	}
	else
	{
		Struct_Cyclorama.VWidth = VWidth;

		Struct_Cyclorama.VColorC = VColorC;

		Struct_Cyclorama.VColorS = VColorS;

		Struct_Cyclorama.VLockColorS = VLockColorS;

		Struct_Cyclorama.VUnlit = VUnlit;

		Struct_Cyclorama.VReflection = VReflection;

		Struct_Cyclorama.VRoughness = VRoughness;

		Struct_Cyclorama.VFog = VFog;

		Struct_Cyclorama.VFogDensity = VFogDensity;
	}*/

	

}

// Called when the game starts or when spawned
void AMetaShoot_Cyclorama::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMetaShoot_Cyclorama::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMetaShoot_Cyclorama::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	AMetaShoot_Cyclorama::UpdateCyclorama();

}

void AMetaShoot_Cyclorama::UpdateCyclorama()
{
	if (BMSAssetActive) {
		this->SetActorHiddenInGame(false);

		//Old Structure version compatibility
		if (needsUpdate)
		{

			if (VWidth != 1000)
			{
				Struct_Cyclorama.VWidth = VWidth;
			}

			if (VColorC != FLinearColor(0.8f, 0.8f, 0.8f))
			{
				Struct_Cyclorama.VColorC = VColorC;
			}

			if (VColorS != FLinearColor(0.05f, 0.05f, 0.05f))
			{
				Struct_Cyclorama.VColorS = VColorS;
			}

			if (VLockColorS != true)
			{
				Struct_Cyclorama.VLockColorS = VLockColorS;
			}

			needsUpdate = false;

		};


		UpdateCycloramaTransform();

		if (Struct_Cyclorama.VCycloramaType == EVBackgroundTypeMS::Cyclorama)
		{
			Cyclorama_Frame00->SetVisibility(true);
			Cyclorama_Frame01->SetVisibility(true);
			Cyclorama_Frame02->SetVisibility(true);
			Cyclorama_Frame03->SetVisibility(true);
			Cyclorama_Frame04->SetVisibility(true);
			Cyclorama_Frame05->SetVisibility(true);
			Cyclorama_Frame06->SetVisibility(true);
			Cyclorama_Frame07->SetVisibility(true);


			Cyclorama_FrameBack01->SetVisibility(true);
			Cyclorama_FrameBack02->SetVisibility(true);
			Cyclorama_FrameBack03->SetVisibility(true);
			Cyclorama_FrameBack04->SetVisibility(true);
			Cyclorama_FrameBack05->SetVisibility(true);
			Cyclorama_FrameBack06->SetVisibility(true);
		}
		else
		{
			Cyclorama_Frame00->SetVisibility(false);
			Cyclorama_Frame01->SetVisibility(false);
			Cyclorama_Frame02->SetVisibility(false);
			Cyclorama_Frame03->SetVisibility(false);
			Cyclorama_Frame04->SetVisibility(false);
			Cyclorama_Frame05->SetVisibility(false);
			Cyclorama_Frame06->SetVisibility(false);
			Cyclorama_Frame07->SetVisibility(false);


			Cyclorama_FrameBack01->SetVisibility(false);
			Cyclorama_FrameBack02->SetVisibility(false);
			Cyclorama_FrameBack03->SetVisibility(false);
			Cyclorama_FrameBack04->SetVisibility(false);
			Cyclorama_FrameBack05->SetVisibility(false);
			Cyclorama_FrameBack06->SetVisibility(false);
		}

		if (Struct_Cyclorama.VCycloramaType == EVBackgroundTypeMS::Room)
		{
			SkirtingBoard01->SetVisibility(true);
			SkirtingBoard02->SetVisibility(true);
			SkirtingBoard03->SetVisibility(true);
		}
		else
		{
			SkirtingBoard01->SetVisibility(false);
			SkirtingBoard02->SetVisibility(false);
			SkirtingBoard03->SetVisibility(false);
		}

		if (Struct_Cyclorama.VCycloramaType != EVBackgroundTypeMS::Dome)
		{
			UEnclosure->SetVisibility(Struct_Cyclorama.VEnclosure);
		}
		else
		{
			UEnclosure->SetVisibility(false);
		}



		Cyclorama_Fog->SetVisibility(Struct_Cyclorama.VFog);
		Cyclorama_Fog->SetFogDensity(Struct_Cyclorama.VFogDensity);

		//Struct_Cyclorama.VTransform = this->GetTransform();

		UpdateCycloramaBP();

		UpdateCycloramaMaterials();
	}
	else {
		this->SetActorHiddenInGame(true);
	}
}

void AMetaShoot_Cyclorama::UpdateCycloramaTransform()
{
	if (Struct_Cyclorama.VCycloramaType != EVBackgroundTypeMS::Dome)
	{
		Cyclorama_C->SetRelativeLocation(FVector(-XOffset, 0.0f, -0.5f));
		Cyclorama_C->SetRelativeScale3D(FVector(1.0f, ((Struct_Cyclorama.VWidth / 2) - 68.291) / 250, 1.0f));
	}
	else
	{
		Cyclorama_C->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Cyclorama_C->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}


	if (Struct_Cyclorama.VCycloramaType == EVBackgroundTypeMS::Cyclorama)
	{
		Cyclorama_C->SetRelativeScale3D(FVector(1.0f, ((Struct_Cyclorama.VWidth / 2) - 68.291) / 250, 1.0f));
		Cyclorama_L->SetRelativeLocation(FVector(-XOffset, -((Struct_Cyclorama.VWidth / 2) - 68.291), -0.5f));
		Cyclorama_R->SetRelativeLocation(FVector(-XOffset, (Struct_Cyclorama.VWidth / 2) - 68.291, -0.5f));
		//68.291 is the width of the side mesh
	}
	else if (Struct_Cyclorama.VCycloramaType == EVBackgroundTypeMS::Room)
	{
		Cyclorama_C->SetRelativeScale3D(FVector(1.0f, Struct_Cyclorama.VWidth / 500, 1.0f));
		Cyclorama_L->SetRelativeLocation(FVector(-XOffset, -Struct_Cyclorama.VWidth / 2, -0.5f));
		Cyclorama_R->SetRelativeLocation(FVector(-XOffset, Struct_Cyclorama.VWidth / 2, -0.5f));
	}
	else if (Struct_Cyclorama.VCycloramaType == EVBackgroundTypeMS::Dome)
	{
		Cyclorama_C->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}

	UEnclosure->SetRelativeScale3D(FVector(1.0f, Struct_Cyclorama.VWidth / 645, 1.0f));
}

void AMetaShoot_Cyclorama::UpdateCycloramaMaterials()
{
	// Get the array of slot names
	//TArray<FName> slotNames = Cyclorama_C->GetMaterialSlotNames();

	// Find the index of the target slot name
	//int32 materialSlot01Index = slotNames.IndexOfByPredicate([&](const FName& name) { return name == FName(TEXT("materialSlot01")); });


	if (Struct_Cyclorama.VLockColorS)
	{
		if (IsValid(Struct_Cyclorama.VMainMaterial))
		{
			switch (Struct_Cyclorama.VCycloramaType)
			{
				case EVBackgroundTypeMS::Cyclorama:
					Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
					Cyclorama_L->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
					Cyclorama_R->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
					break;

				case EVBackgroundTypeMS::Room:
					Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
					Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot02")), Struct_Cyclorama.VMainMaterial);
					Cyclorama_L->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
					Cyclorama_R->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
					SkirtingBoard01->SetMaterial(0, Struct_Cyclorama.VMainMaterial);
					SkirtingBoard02->SetMaterial(0, Struct_Cyclorama.VMainMaterial);
					SkirtingBoard03->SetMaterial(0, Struct_Cyclorama.VMainMaterial);
					break;

				case EVBackgroundTypeMS::Dome:
					Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
					break;
			}

			UEnclosure->SetMaterial(0, Struct_Cyclorama.VMainMaterial);
		}
		else
		{
			UMaterialInterface* cycloramaMaterial01 = nullptr;

			if (!Struct_Cyclorama.VUnlit)
			{
				if (IsValid(VMaterialLit))
				{
					cycloramaMaterial01 = VMaterialLit;
				}
			}
			else
			{
				if (IsValid(VMaterialUnlit))
				{
					cycloramaMaterial01 = VMaterialUnlit;
				}
			}
			
			UMaterialInstanceDynamic* VMainMaterialInstance = UMaterialInstanceDynamic::Create(cycloramaMaterial01, this);
			VMainMaterialInstance->SetVectorParameterValue(FName("CycloramaColor"), Struct_Cyclorama.VColorC);

			switch (Struct_Cyclorama.VCycloramaType)
			{
			case EVBackgroundTypeMS::Cyclorama:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				Cyclorama_L->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				Cyclorama_R->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				break;

			case EVBackgroundTypeMS::Room:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot02")), VMainMaterialInstance);
				Cyclorama_L->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				Cyclorama_R->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				SkirtingBoard01->SetMaterial(0, VMainMaterialInstance);
				SkirtingBoard02->SetMaterial(0, VMainMaterialInstance);
				SkirtingBoard03->SetMaterial(0, VMainMaterialInstance);
				break;

			case EVBackgroundTypeMS::Dome:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				break;
			}

			UEnclosure->SetMaterial(0, VMainMaterialInstance);
			
		}
	}
	else
	{
		if (IsValid(Struct_Cyclorama.VMainMaterial))
		{
			switch (Struct_Cyclorama.VCycloramaType)
			{
			case EVBackgroundTypeMS::Cyclorama:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
				break;

			case EVBackgroundTypeMS::Room:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
				Cyclorama_L->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
				Cyclorama_R->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
				SkirtingBoard01->SetMaterial(0, Struct_Cyclorama.VMainMaterial);
				SkirtingBoard02->SetMaterial(0, Struct_Cyclorama.VMainMaterial);
				SkirtingBoard03->SetMaterial(0, Struct_Cyclorama.VMainMaterial);
				break;

			case EVBackgroundTypeMS::Dome:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VMainMaterial);
				break;
			}

			UEnclosure->SetMaterial(0, Struct_Cyclorama.VMainMaterial);
		}
		else
		{
			UMaterialInterface* cycloramaMaterial01 = nullptr;

			if (!Struct_Cyclorama.VUnlit)
			{
				if (IsValid(VMaterialLit))
				{
					cycloramaMaterial01 = VMaterialLit;
				}
			}
			else
			{
				if (IsValid(VMaterialUnlit))
				{
					cycloramaMaterial01 = VMaterialUnlit;
				}
			}

			UMaterialInstanceDynamic* VMainMaterialInstance = UMaterialInstanceDynamic::Create(cycloramaMaterial01, this);
			VMainMaterialInstance->SetVectorParameterValue(FName("CycloramaColor"), Struct_Cyclorama.VColorC);

			switch (Struct_Cyclorama.VCycloramaType)
			{
			case EVBackgroundTypeMS::Cyclorama:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				break;

			case EVBackgroundTypeMS::Room:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				Cyclorama_L->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				Cyclorama_R->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				SkirtingBoard01->SetMaterial(0, VMainMaterialInstance);
				SkirtingBoard02->SetMaterial(0, VMainMaterialInstance);
				SkirtingBoard03->SetMaterial(0, VMainMaterialInstance);
				break;

			case EVBackgroundTypeMS::Dome:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot01")), VMainMaterialInstance);
				break;
			}

			UEnclosure->SetMaterial(0, VMainMaterialInstance);
		}

		if (IsValid(Struct_Cyclorama.VSecondaryMaterial))
		{
			switch (Struct_Cyclorama.VCycloramaType)
			{
			case EVBackgroundTypeMS::Cyclorama:
				Cyclorama_L->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VSecondaryMaterial);
				Cyclorama_R->SetMaterialByName(FName(TEXT("materialSlot01")), Struct_Cyclorama.VSecondaryMaterial);
				break;

			case EVBackgroundTypeMS::Room:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot02")), Struct_Cyclorama.VSecondaryMaterial);
				break;

			case EVBackgroundTypeMS::Dome:
				break;
			}
		}
		else
		{
			UMaterialInterface* cycloramaMaterial01 = nullptr;

			if (!Struct_Cyclorama.VUnlit)
			{
				if (IsValid(VMaterialLit))
				{
					cycloramaMaterial01 = VMaterialLit;
				}
			}
			else
			{
				if (IsValid(VMaterialUnlit))
				{
					cycloramaMaterial01 = VMaterialUnlit;
				}
			}

			UMaterialInstanceDynamic* VSecondaryMaterialInstance = UMaterialInstanceDynamic::Create(cycloramaMaterial01, this);
			VSecondaryMaterialInstance->SetVectorParameterValue(FName("CycloramaColor"), Struct_Cyclorama.VColorS);

			switch (Struct_Cyclorama.VCycloramaType)
			{
			case EVBackgroundTypeMS::Cyclorama:
				Cyclorama_L->SetMaterialByName(FName(TEXT("materialSlot01")), VSecondaryMaterialInstance);
				Cyclorama_R->SetMaterialByName(FName(TEXT("materialSlot01")), VSecondaryMaterialInstance);
				break;

			case EVBackgroundTypeMS::Room:
				Cyclorama_C->SetMaterialByName(FName(TEXT("materialSlot02")), VSecondaryMaterialInstance);
				break;

			case EVBackgroundTypeMS::Dome:
				break;
			}
		}
	}
	
}