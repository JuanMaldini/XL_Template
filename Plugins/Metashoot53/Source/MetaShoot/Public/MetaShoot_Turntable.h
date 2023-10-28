// Copyright 2023, VINZI Studio S.L. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/TimelineComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"

#include "MetaShoot_Manifest.h"

#include "MetaShoot_Turntable.generated.h"

//UENUM(Category = "Turntable", meta = (DisplayName = "UV Checker", DisplayPriority = 8))
//enum class EVUVChecker : uint8
//{
//	None,
//	UVChecker01,
//	UVChecker02,
//	UVChecker03
//};


UCLASS()
class METASHOOT_API AMetaShoot_Turntable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetaShoot_Turntable();

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		bool BMSAssetActive = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Turntable", meta = (DisplayName = "Turntable", DisplayPriority = 0, ShowOnlyInnerProperties))
		FSMetaShoot_Turntable Struct_Turntable;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		bool needsUpdate = true;

	UPROPERTY(BlueprintReadWrite, Category = "Turntable")
		bool  VEnableRotation = true;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


	//Settings

	// OLD

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Rotate", DisplayPriority = -1))
		bool  VRotate = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Rotation Total (degrees)", DisplayPriority = 0, ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0", UIMax = "360.0"))
		float VDegrees = 360;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Rotation Duration (s)", DisplayPriority = 1, ClampMin = "0.1", ClampMax = "500.0", UIMin = "0.1", UIMax = "60.0"))
		float VRotationTime = 5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Delay Start (s)", DisplayPriority = 2, ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "5.0"))
		float VDelay = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Loop", DisplayPriority = 3))
		bool  VLoop = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Clockwise", DisplayPriority = 4))
		bool  VClockwise = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Actor", DisplayPriority = 5))
		AActor* VActor = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Mesh", DisplayPriority = 6))
		UStaticMesh* VMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Material", DisplayPriority = 7))
		UMaterial* VMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Mesh Transform", DisplayPriority = 8, AllowPrivateAccess = "true"))
		FTransform VTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Base Scale", DisplayPriority = 10, ClampMin = "0.1", ClampMax = "10.0", UIMin = "0.1", UIMax = "5.0"))
		float VBaseScale = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Base Hidden in Render", DisplayPriority = 11))
		bool  VHideBase = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Preview Rotation Axis", DisplayPriority = 12))
		bool  VPreviewZ = true;*/



	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		bool  VRotate = true;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		float VDegrees = 360;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		float VRotationTime = 5;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		float VDelay = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		bool  VLoop = true;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		bool  VClockwise = true;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		AActor* VActor = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		UStaticMesh* VMesh;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		UMaterial* VMaterial;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		FTransform VTransform;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		float VBaseScale = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		bool  VHideBase = true;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		bool  VPreviewZ = true;

	//Dummy for change property

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		FTransform VTransformChild;
		
		


	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "UV Checker", DisplayPriority = 9))
		//bool VUVChecker = false;

	//bool VPreviousUVChecker = VUVChecker;

	AActor* VActorPrevious;


	//Components

	UPROPERTY()
		USceneComponent* Turntable_Root;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		UStaticMeshComponent* TurntableBase;

	UPROPERTY(BlueprintReadWrite, Category = "Turntable")
		UChildActorComponent* VActorComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Turntable")
		UStaticMeshComponent* VMeshComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Turntable")
		UArrowComponent* VArrowZ;

	UPROPERTY(BlueprintReadWrite, Category = "Turntable")
		float VFramerate;


	//Functions

	UFUNCTION(Category = "Turntable")
		void TimelineProgress(float Value);

	UFUNCTION(Category = "Turntable")
		void StartRotation();

	UFUNCTION(BlueprintImplementableEvent, Category = "Turntable")
		void UpdateUVChecker();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	UPROPERTY()
		UCurveFloat* CurveFloat;

	/*UPROPERTY(EditAnywhere, Category = "Timeline")
		FRichCurve VRichCurve;*/

	UPROPERTY()
		float StartRot;

	UPROPERTY()
		float EndRot;

	UPROPERTY()
		float StartTime;

	UPROPERTY()
		bool BStarted = false;

	UPROPERTY()
		bool BFinished = false;

	UPROPERTY()
		int32 Iframe = 0;

	/*UPROPERTY(EditAnywhere, Category = "Timeline")
		float ZOffset;*/


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

};
