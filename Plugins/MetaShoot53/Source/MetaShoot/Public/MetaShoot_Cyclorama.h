// Copyright 2023, VINZI Studio S.L. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "MetaShoot_Manifest.h"

#include "MetaShoot_Cyclorama.generated.h"

UCLASS()
class METASHOOT_API AMetaShoot_Cyclorama : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetaShoot_Cyclorama();

	//Variables

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		bool BMSAssetActive = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Cyclorama", meta = (DisplayName = "Cyclorama", DisplayPriority = 0, ShowOnlyInnerProperties))
		FSMetaShoot_Cyclorama Struct_Cyclorama;


	//OLD VARIABLES

	/*UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		float VWidth;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		FLinearColor VColorC;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		FLinearColor VColorS;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		bool VLockColorS;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		bool VUnlit;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		float VReflection;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		float VRoughness;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		bool VFog;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		float VFogDensity;*/

	//

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		float VWidth = 1000;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		FLinearColor VColorC = FLinearColor(0.8f, 0.8f, 0.8f);

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		FLinearColor VColorS = FLinearColor(0.05f, 0.05f, 0.05f);

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		bool VLockColorS = true;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		bool VUnlit = false;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		float VReflection = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		float VRoughness = 0.5;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		bool VFog;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		float VFogDensity = 0.2;


	//


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cyclorama")
		UMaterialInterface* VMaterialLit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cyclorama")
		UMaterialInterface* VMaterialUnlit;



	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		bool needsUpdate = true;


	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		float XOffset = 216.0;



	//Components

	UPROPERTY()
		USceneComponent* Cyclorama_Root;

	UPROPERTY(BlueprintReadWrite, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_C;

	UPROPERTY(BlueprintReadWrite, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_R;

	UPROPERTY(BlueprintReadWrite, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_L;

	UPROPERTY(BlueprintReadWrite, Category = "Cyclorama")
		UStaticMeshComponent* UEnclosure;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_Frame00;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_Frame01;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_Frame02;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_Frame03;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_Frame04;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_Frame05;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_Frame06;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_Frame07;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_FrameBack01;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_FrameBack02;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_FrameBack03;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_FrameBack04;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_FrameBack05;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cyclorama")
		UStaticMeshComponent* Cyclorama_FrameBack06;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cyclorama")
		UStaticMeshComponent* SkirtingBoard01;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cyclorama")
		UStaticMeshComponent* SkirtingBoard02;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cyclorama")
		UStaticMeshComponent* SkirtingBoard03;

	/*UPROPERTY(BlueprintReadOnly)
		UDecalComponent* Cyclorama_Decal;*/

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UExponentialHeightFogComponent* Cyclorama_Fog;

	//Material Instances

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UMaterialInstanceDynamic* VCycloramaCMI;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UMaterialInstanceDynamic* VCycloramaSMIR;

	UPROPERTY(BlueprintReadOnly, Category = "Cyclorama")
		UMaterialInstanceDynamic* VCycloramaSMIL;

	//Functions

	UFUNCTION(BlueprintCallable, Category = "Cyclorama")
		void UpdateCyclorama();

	UFUNCTION(Category = "Cyclorama")
		void UpdateCycloramaTransform();

	UFUNCTION(Category = "Cyclorama")
		void UpdateCycloramaMaterials();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Cyclorama")
		void UpdateCycloramaBP();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

};
