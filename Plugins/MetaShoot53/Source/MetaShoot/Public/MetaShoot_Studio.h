// Copyright 2023, VINZI Studio S.L. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "MetaShoot_Manifest.h"
#include "MetaShoot_InGame.h"

#include "MetaShoot_Studio.generated.h"

UCLASS()
class METASHOOT_API AMetaShoot_Studio : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetaShoot_Studio();

	UPROPERTY(BlueprintReadOnly, Category = "Studio")
		bool BMSAssetActive = true;

	UPROPERTY(BlueprintReadWrite, Category = "Studio")
		FSMetaShoot_Studio Struct_Studio;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Studio", meta = (DisplayName = "in-Game UI - BETA", DisplayPriority = 0))
		bool VInGameUI = false;

	UPROPERTY(BlueprintReadWrite, Category = "Studio")
		UMetaShoot_InGame* VUserWidget;

	UPROPERTY(BlueprintReadWrite, Interp, Category = "Studio")
		FString PresetName = "";


	UFUNCTION(BlueprintCallable, Category = "Studio")
		void PresetsLoadStudio(const FString& PresetNameString, FSMetaShoot_Studio& StudioStruct);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Studio")
		void UpdateFullStudio();


/*#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	UPROPERTY()
		TSubclassOf<AMetaShoot_Cyclorama> VCyclorama;

};
