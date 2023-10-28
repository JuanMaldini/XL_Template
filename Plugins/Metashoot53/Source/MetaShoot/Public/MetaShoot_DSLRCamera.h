// Copyright 2023, VINZI Studio S.L. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "CineCameraActor.h"

#include "MetaShoot_Manifest.h"

#include "MetaShoot_DSLRCamera.generated.h"

/**
 * 
 */
UCLASS()
class METASHOOT_API AMetaShoot_DSLRCamera : public ACineCameraActor
{
	GENERATED_BODY()

public:

	/*#if WITH_EDITOR
		virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif*/

	/*UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UStaticMeshComponent* CameraMesh02;*/

	UPROPERTY(BlueprintReadOnly, Category = "DSLR Camera")
		bool BMSAssetActive = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, Category = "Current Camera Settings", meta = (DisplayName = "DSLR Camera", DisplayPriority = 0, ShowOnlyInnerProperties))
		FSMetaShoot_DSLR DSLR;

	UPROPERTY(BlueprintReadOnly, Category = "DSLR Camera")
		bool needsUpdate = true;

	// OLD

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current Camera Settings", meta = (DisplayName = "DSLR Mesh Hidden in Render", DisplayPriority = 1))
		bool VCameraMeshHidden;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Current Camera Settings", meta = (DisplayName = "DSLR Mesh Scale", DisplayPriority = 2))
		float VCameraMeshScale = 2.5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Current Camera Settings", meta = (DisplayName = "Target", DisplayPriority = 3))
		AActor* VActorToTrack;
	*/

	UPROPERTY(BlueprintReadOnly, Category = "DSLR Camera")
		bool VCameraMeshHidden;

	UPROPERTY(BlueprintReadOnly, Category = "DSLR Camera")
		float VCameraMeshScale = 2.5;

	UPROPERTY(BlueprintReadOnly, Category = "DSLR Camera")
		AActor* VActorToTrack;




	//UFUNCTION(BlueprintCallable, CallInEditor, Category = "Current Camera Settings", meta = (DisplayName = "Fix DOF", DisplayPriority = 0, ToolTip = "Runs the command r.TemporalAA.Upsampling 0 to fix the Depth Of Field. Credit to William Faucher"))
	//	void FixDepthOfField();

	UFUNCTION(BlueprintImplementableEvent, Category = "DSLR")
		void FixDOFBP();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "DSLR")
		void UpdateDSLR();

	UFUNCTION(BlueprintCallable, Category = "DSLR")
		void DefineFocusTarget();



	virtual void OnConstruction(const FTransform& Transform) override;
	
};
