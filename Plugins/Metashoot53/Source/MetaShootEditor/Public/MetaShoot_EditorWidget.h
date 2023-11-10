// Copyright 2023, VINZI Studio S.L. All rights reserved

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"

#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/MovieScene/Public/MovieScene.h"

#include "HTTP.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#include "MetaShoot_Manifest.h"

#include "EditorUtilityWidgetBlueprint.h"

#include "MetaShoot_EditorWidget.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EVRenderQualityMS : uint8
{
	Low,
	Medium,
	High,
	UltraHigh,
	Custom
};


USTRUCT(BlueprintType)
struct METASHOOTEDITOR_API FCustomRenderQuality
{
	FCustomRenderQuality(int32 InX = 8, int32 InY = 2) : SpatialSamples(InX), TemporalSamples(InY) {}

	GENERATED_BODY()

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Render", meta = (ClampMin = 1, ClampMax = 7680))
		int32 SpatialSamples;

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Render", meta = (ClampMin = 1, ClampMax = 7680))
		int32 TemporalSamples;
};

UCLASS()
class METASHOOTEDITOR_API UMetaShoot_EditorWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
	public:
	UMetaShoot_EditorWidget();
	~UMetaShoot_EditorWidget();

	UFUNCTION(BlueprintImplementableEvent, Category = "My Custom Function")
		void MyExposedFunction();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "MyScriptingLibrary sample test testing"), Category = "MyScriptingLibraryTesting")
		static float MyScriptingLibrarySampleFunction(float Param);

	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		void checkLog();

	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		void authenticate();

	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		void logout();


	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		void GetSample();

	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		void PostSample();


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "EditorWidget")
		void LoggedEvent();


	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		void MSRender();

	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		TArray<FString> PresetsRefreshList();

	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		void PresetsSaveStudio(const FSMetaShoot_Studio& StudioStruct);

	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		void PresetsLoadStudio(FSMetaShoot_Studio& StudioStruct);

	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		void PresetsDeleteStudio();


	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		TSubclassOf<AMetaShoot_Preset> CheckMSPresetClass(UObject* BlueprintAsset);

	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		TSubclassOf<AActor> CheckActorClass(UObject* BlueprintAsset);



	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		void getViewPortCameraPosLoc();


	//UPROPERTY()
		//UMoviePipelineMasterConfig* MPMasterConfig;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		FVector viewPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		FRotator viewRot;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		FString Vemail;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		FString Vpassword;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EditorWidget")
		FString VLog;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		FString VphpResponse;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EditorWidget")
		bool BMSActive = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		ULevelSequence* MSLevelSequence;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		int32 MSEndFrame = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EditorWidget")
		bool BShowNewsLog = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EditorWidget")
		FString VNewsLog;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EditorWidget")
		FString MSVersion;



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Render", meta = (DisplayName = "Quality", DisplayPriority = 0))
		EVRenderQualityMS VQuality = EVRenderQualityMS::Medium;

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Render", meta = (DisplayName = "Samples", DisplayPriority = 0, EditCondition = "VQuality == EVRenderQualityMS::Custom"))
		FCustomRenderQuality VSamples;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		FString presetsFullPath = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		FString VPreset = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		FString NewPresetName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EditorWidget")
		bool VSaveLocal = false;




	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "EditorWidget")
		void UpdateNewsLog();

	UFUNCTION(BlueprintCallable, Category = "EditorWidget")
		static bool IsNewerVersion(FString version1, FString version2);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "EditorWidget")
		void MetaShootRender();

	

	//virtual void Tick(float DeltaTime) override;

private:

	void OnResponseReceivedSample(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully);

	void printRequestResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully);

	void printLogNews(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully);

	void loginChecked(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully);

	void updateLog(FString Case);

	void updateLastCheck();

	void applyLicenseToMetaShootActors(FString Case);

	void loggedOutMessage();

	void checkRayTracing();
	
};