// Copyright 2023, VINZI Studio S.L. All rights reserved

#pragma once

#include "CoreMinimal.h"

#include "MetaShoot_StudioStructure.generated.h"

class AMetaShoot_Preset;


/**
 * 
 */
class METASHOOT_API MetaShoot_StudioStructure
{
public:
	MetaShoot_StudioStructure();
	~MetaShoot_StudioStructure();
};

UENUM(BlueprintType, Category = "Softbox", meta = (DisplayName = "Light Type"))
enum class EVLightTypeMS : uint8
{
	Softbox_60x60,
	Softbox_50x70,
	Softbox_30x120,
	Softbox_70x70_Octagon,
	Spotlight,
	RingLight,
	LightWand
};

UENUM(BlueprintType, Category = "Softbox", meta = (DisplayName = "Support"))
enum class EVLightSupportMS : uint8
{
	Automatic,
	Tripod,
	Scissors,
	None
};

UENUM(Category = "Softbox", meta = (DisplayName = "Intensity Units"))
enum class EVLightUnitsMS : uint8
{
	Unitless,
	Candelas,
	Lumens
};

UENUM(BlueprintType, Category = "Cyclorama", meta = (DisplayName = "Background Type"))
enum class EVBackgroundTypeMS : uint8
{
	Cyclorama,
	Room,
	Dome
};


USTRUCT(BlueprintType)
struct FSMetaShoot_Cyclorama
{
GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Cyclorama")
		FTransform VTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Cyclorama", meta = (DisplayName = "Background Type", DisplayPriority = 0))
		EVBackgroundTypeMS VCycloramaType = EVBackgroundTypeMS::Cyclorama;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Cyclorama", meta = (DisplayName = "Enclosure", DisplayPriority = 1, EditCondition = "VCycloramaType != EVBackgroundTypeMS::Dome"))
		bool VEnclosure = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Cyclorama", meta = (DisplayName = "Width", DisplayPriority = 2, ClampMin = "150.0", ClampMax = "1500.0", UIMin = "150.0", UIMax = "1500.0", EditCondition = "VCycloramaType != EVBackgroundTypeMS::Dome"))
		float VWidth = 1000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Cyclorama", meta = (DisplayName = "Main Color", DisplayPriority = 3, EditCondition = "!IsValid(VMainMaterial)"))
		FLinearColor VColorC = FLinearColor(0.8f, 0.8f, 0.8f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cyclorama", meta = (DisplayName = "Override Main Material", DisplayPriority = 4))
		UMaterialInterface* VMainMaterial = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Cyclorama", meta = (DisplayName = "Secondary Color", DisplayPriority = 5, EditCondition = "!VLockColorS && !IsValid(VSecondaryMaterial)"))
		FLinearColor VColorS = FLinearColor(0.05f, 0.05f, 0.05f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cyclorama", meta = (DisplayName = "Override Secondary Material", DisplayPriority = 6, EditCondition = "!VLockColorS"))
		UMaterialInterface* VSecondaryMaterial = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Cyclorama", meta = (DisplayName = "Single Material", DisplayPriority = 7, EditCondition = "VCycloramaType != EVBackgroundTypeMS::Dome"))
		bool VLockColorS = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Cyclorama", meta = (DisplayName = "Unlit", DisplayPriority = 8, EditCondition = "!IsValid(VMainMaterial)"))
		bool VUnlit = false;

	UPROPERTY(BlueprintReadWrite, Category = "Cyclorama", meta = (DisplayName = "Reflection", DisplayPriority = 9, ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float VReflection = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Cyclorama", meta = (DisplayName = "Roughness", DisplayPriority = 10, ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float VRoughness = 0.5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Cyclorama", meta = (DisplayName = "Fog", DisplayPriority = 11))
		bool VFog = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Cyclorama", meta = (DisplayName = "Fog Density", DisplayPriority = 12, ClampMin = "0.0", ClampMax = "5.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "VFog"))
		float VFogDensity = 0.2;

};

USTRUCT(BlueprintType)
struct FSMetaShoot_Light
{
GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Softbox")
		FTransform VTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Softbox", meta = (DisplayName = "Light Type", DisplayPriority = 0))
		EVLightTypeMS VLightType = EVLightTypeMS::Softbox_60x60;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Softbox", meta = (DisplayName = "Intensity - Candelas", DisplayPriority = 1, ClampMin = "0.0", ClampMax = "2000.0", UIMin = "0.0", UIMax = "750.0"))
		float VLightIntensity = 100;

	UPROPERTY(BlueprintReadWrite, Category = "Softbox", meta = (DisplayName = "Intensity Units", DisplayPriority = 2))
		EVLightUnitsMS VLightUnits = EVLightUnitsMS::Candelas;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Softbox", meta = (DisplayName = "Temperature", DisplayPriority = 3, ClampMin = "1200.0", ClampMax = "12000.0", UIMin = "1200.0", UIMax = "12000.0", EditCondition = "VLightTemperatureBool"))
		int32 VLightTemperature = 6500;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Softbox", meta = (DisplayName = "Use Temperature", DisplayPriority = 4))
		bool VLightTemperatureBool = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Softbox", meta = (DisplayName = "Tint", DisplayPriority = 5))
		FLinearColor VLightTint = FLinearColor(1.0f, 1.0f, 1.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Softbox", meta = (DisplayName = "Diffuser", DisplayPriority = 6, EditCondition = "VLightType != EVLightTypeMS::Spotlight && VLightType != EVLightTypeMS::Ringlight && VLightType != EVLightTypeMS::LightWand"))
		bool VLightDifuserBool = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Softbox", meta = (DisplayName = "Grid", DisplayPriority = 7, EditCondition = "VLightDifuserBool && VLightType != EVLightTypeMS::Spotlight && VLightType != EVLightTypeMS::RingLight && VLightType != EVLightTypeMS::LightWand"))
		bool VLightGridBool = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Softbox", meta = (DisplayName = "Support", DisplayPriority = 8))
		EVLightSupportMS VLightSupport = EVLightSupportMS::Automatic;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Softbox", meta = (DisplayName = "Scissors Segments", DisplayPriority = 9))
		int32 VLightScissorsSegments = 8;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Softbox", meta = (DisplayName = "Actor to Track", DisplayPriority = 10))
		AActor* VActorToTrack = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Softbox")
		FString VTargetName = "";

	UPROPERTY(BlueprintReadWrite, Category = "Softbox")
		int32 VTargetID = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Softbox", meta = (DisplayName = "Rotation", DisplayPriority = 11, ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0", UIMax = "360.0", EditCondition = "VActorToTrack != nullptr"))
		float VLightRotation = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Softbox", meta = (DisplayName = "Mesh Hidden in Render", DisplayPriority = 12))
		bool VHideMesh = false;
};

USTRUCT(BlueprintType)
struct FSMetaShoot_LightBank
{
GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "LightBank")
		FTransform VTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "LightBank", meta = (DisplayName = "Intensity - Candelas", DisplayPriority = 1, ClampMin = "0.0", ClampMax = "2000.0", UIMin = "0.0", UIMax = "750.0"))
		float VLightIntensity = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "LightBank", meta = (DisplayName = "Temperature", DisplayPriority = 3, ClampMin = "1200.0", ClampMax = "12000.0", UIMin = "1200.0", UIMax = "12000.0", EditCondition = "VLightTemperatureBool"))
		int32 VLightTemperature = 6500;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LightBank", meta = (DisplayName = "Use Temperature", DisplayPriority = 4))
		bool VLightTemperatureBool = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "LightBank", meta = (DisplayName = "Tint", DisplayPriority = 5))
		FLinearColor VLightTint = FLinearColor(1.0f, 1.0f, 1.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LightBank", meta = (DisplayName = "Actor to Track", DisplayPriority = 10))
		AActor* VActorToTrack = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "LightBank")
		FString VTargetName = "";

	UPROPERTY(BlueprintReadWrite, Category = "LightBank")
		int32 VTargetID = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LightBank", meta = (DisplayName = "Mesh Hidden in Render", DisplayPriority = 12))
		bool VHideMesh = false;

};

USTRUCT(BlueprintType)
struct FSMetaShoot_Target
{
GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Target")
		FTransform VTransform;

	UPROPERTY(BlueprintReadWrite, Category = "Target")
		FLinearColor VTint = FLinearColor(1.0f, 1.0f, 1.0f);

	UPROPERTY(BlueprintReadWrite, Category = "Target")
		FString VTargetName = "";

	UPROPERTY(BlueprintReadWrite, Category = "Target")
		int32 VTargetID = 0;
};

USTRUCT(BlueprintType)
struct FSMetaShoot_DSLR
{
GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "DSLR Camera")
		FTransform VTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current Camera Settings", meta = (DisplayName = "DSLR Mesh Hidden in Render", DisplayPriority = 1))
		bool VCameraMeshHidden = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Current Camera Settings", meta = (DisplayName = "DSLR Mesh Scale", DisplayPriority = 2))
		float VCameraMeshScale = 2.5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current Camera Settings", meta = (DisplayName = "Target", DisplayPriority = 3))
		AActor* VActorToTrack = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "DSLR Camera")
		FString VTargetName = "";

	UPROPERTY(BlueprintReadWrite, Category = "DSLR Camera")
		int32 VTargetID = 0;
};

USTRUCT(BlueprintType)
struct FSMetaShoot_Turntable
{
GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Turntable")
		FTransform VTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Rotate", DisplayPriority = -1))
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
		UStaticMesh* VMesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Material", DisplayPriority = 7))
		UMaterial* VMaterial = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Mesh Transform", DisplayPriority = 8, AllowPrivateAccess = "true"))
		FTransform VTransformChild;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Base Scale", DisplayPriority = 10, ClampMin = "0.1", ClampMax = "10.0", UIMin = "0.1", UIMax = "5.0"))
		float VBaseScale = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Base Hidden in Render", DisplayPriority = 11))
		bool  VHideBase = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turntable", meta = (DisplayName = "Preview Rotation Axis", DisplayPriority = 12))
		bool  VPreviewZ = true;
};


USTRUCT(BlueprintType)
struct FSMetaShoot_Rail
{
GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Rail System")
		FTransform VTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rail System", meta = (DisplayName = "Beam Separation", DisplayPriority = 0, ClampMin = "100.0", ClampMax = "500.0", UIMin = "100.0", UIMax = "500.0"))
		float VSeparation = 375;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rail System", meta = (DisplayName = "Beam Length", DisplayPriority = 1, ClampMin = "500.0", ClampMax = "1500.0", UIMin = "500.0", UIMax = "1500.0"))
		float VLength = 1000;
};



USTRUCT(BlueprintType)
struct FSMetaShoot_Studio
{
GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaShoot")
		TArray<FSMetaShoot_Cyclorama> Cycloramas;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaShoot")
        TArray<FSMetaShoot_Light> Lights;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaShoot")
		TArray<FSMetaShoot_Target> Targets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaShoot")
		TArray<FSMetaShoot_LightBank> LightBanks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaShoot")
		TArray<FSMetaShoot_DSLR> DSLRs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaShoot")
		TArray<FSMetaShoot_Turntable> Turntables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaShoot")
		TArray<FSMetaShoot_Rail> Rails;
};


USTRUCT(BlueprintType)
struct FSMetaShoot_Stage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Batch", meta = (DisplayName = "Preset", DisplayPriority = 0, BlueprintBaseOnly))
		TSubclassOf <AMetaShoot_Preset> VPresetAsset = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Batch")
		FString VPreset = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batch", meta = (DisplayName = "Model", DisplayPriority = 2))
		TAssetPtr<UObject> VModel = nullptr;

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stager", meta = (DisplayName = "Model", DisplayPriority = 2))
		TSubclassOf<UObject> VModel = nullptr;*/

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stager", meta = (DisplayName = "Mesh", DisplayPriority = 2))
		UStaticMesh* VMesh = nullptr;*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Batch", meta = (DisplayName = "Model Transform", DisplayPriority = 3, AllowPreserveRatio))
		FTransform VTransform;

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stager", meta = (DisplayName = "Override Material", DisplayPriority = 3))
		bool  VOverrideMaterial = false;*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Batch", meta = (DisplayName = "Override Material", DisplayPriority = 4))
		UMaterialInterface* VMaterial = nullptr;


	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stager", meta = (DisplayName = "Duration | Frames", DisplayPriority = 6))
		int32 VDuration = 1;*/

};

USTRUCT(BlueprintType)
struct FBatchOptions
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BatchOptions", meta = (DisplayName = "Add Loaded Items", DisplayPriority = 0))
		bool BAddLoaded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BatchOptions", meta = (DisplayName = "Enable Tunrtable Rotation", DisplayPriority = 1))
		bool BEnableTurntable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BatchOptions", meta = (DisplayName = "Snap Models to Floor", DisplayPriority = 2))
		bool BSnapFloor = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BatchOptions", meta = (DisplayName = "Auto Frame Camera", DisplayPriority = 3))
		bool BAutoFrameCamera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BatchOptions", meta = (DisplayName = "Frame Ratio", DisplayPriority = 4, EditCondition = "BAutoFrameCamera == true"))
		float VFrameRatio = 1.3;
};