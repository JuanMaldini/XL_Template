// Copyright 2023, VINZI Studio S.L. All rights reserved


#include "MetaShoot_Studio.h"

#include "VINZI_JsonToStruct.h"


// Sets default values
AMetaShoot_Studio::AMetaShoot_Studio()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMetaShoot_Studio::BeginPlay()
{
	Super::BeginPlay();

	//UClass* WidgetClass = UMetaShoot_InGame::StaticClass();

	//UUserWidget* VUserWidgetContainer = CreateWidget<UMetaShoot_InGame>(GetWorld(), WidgetClass);

	if (VInGameUI && VUserWidget->IsValidLowLevel()) {
		//VUserWidget->AddToViewport();
	}
	
	/*const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();
	GetWorld()->SpawnActor<AMetaShoot_Cyclorama>(VCyclorama, Location, Rotation);*/
}

// Called every frame
void AMetaShoot_Studio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMetaShoot_Studio::OnConstruction(const FTransform& Transform)
{
	
}

FString presetsFullPath = "";
FString MetaShootEnginePath = FPaths::ConvertRelativePathToFull(FPaths::RootDir()) + TEXT("Engine/Plugins/VINZI/MetaShoot");
FString ProjectPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());

VINZI_JsonToStruct VINZIJsonToStructInst;


void AMetaShoot_Studio::PresetsLoadStudio(const FString& PresetNameString, FSMetaShoot_Studio& StudioStruct)
{
	//Reset Struct
	StudioStruct = FSMetaShoot_Studio();

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	presetsFullPath = MetaShootEnginePath + TEXT("/Presets/") + PresetNameString + TEXT(".vnzms");

	if (!PlatformFile.FileExists(*presetsFullPath))
	{
		presetsFullPath = ProjectPath + TEXT("Source/MetaShoot/Presets/") + PresetNameString + TEXT(".vnzms");
	}

	//if (FPaths::FileExists(presetsFullPath))
	if (PlatformFile.FileExists(*presetsFullPath))
	{

		// Read the JSON file into a string
		FString JsonString;
		FFileHelper::LoadFileToString(JsonString, *presetsFullPath);

		// Deserialize the JSON string into a JSON value
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			TArray<TSharedPtr<FJsonValue>> CycloramasArray = JsonObject->GetArrayField("cycloramas");
			for (const TSharedPtr<FJsonValue>& CycloramaValue : CycloramasArray)
			{
				FSMetaShoot_Cyclorama CycloramaStruct;

				TSharedPtr<FJsonObject> CycloramaObject = CycloramaValue->AsObject();

				VINZIJsonToStructInst.VINZIstruct_Transform(CycloramaObject, "vTransform", CycloramaStruct.VTransform);

				VINZIJsonToStructInst.VINZIstruct_LinearColor(CycloramaObject, "vColorC", CycloramaStruct.VColorC);
				VINZIJsonToStructInst.VINZIstruct_LinearColor(CycloramaObject, "vColorS", CycloramaStruct.VColorS);

				VINZIJsonToStructInst.VINZIstruct_Bool(CycloramaObject, "vLockColorS", CycloramaStruct.VLockColorS);
				VINZIJsonToStructInst.VINZIstruct_Bool(CycloramaObject, "vUnlit", CycloramaStruct.VUnlit);
				VINZIJsonToStructInst.VINZIstruct_Bool(CycloramaObject, "vFog", CycloramaStruct.VFog);

				VINZIJsonToStructInst.VINZIstruct_Float(CycloramaObject, "vWidth", CycloramaStruct.VWidth);
				VINZIJsonToStructInst.VINZIstruct_Float(CycloramaObject, "vReflection", CycloramaStruct.VReflection);
				VINZIJsonToStructInst.VINZIstruct_Float(CycloramaObject, "vRoughness", CycloramaStruct.VRoughness);
				VINZIJsonToStructInst.VINZIstruct_Float(CycloramaObject, "vFogDensity", CycloramaStruct.VFogDensity);

				StudioStruct.Cycloramas.Add(CycloramaStruct);

			}

			TArray<TSharedPtr<FJsonValue>> LightsArray = JsonObject->GetArrayField("lights");
			for (const TSharedPtr<FJsonValue>& LightValue : LightsArray)
			{
				FSMetaShoot_Light LightStruct;

				TSharedPtr<FJsonObject> LightObject = LightValue->AsObject();

				VINZIJsonToStructInst.VINZIstruct_Transform(LightObject, "vTransform", LightStruct.VTransform);

				VINZIJsonToStructInst.VINZIstruct_Float(LightObject, "vLightIntensity", LightStruct.VLightIntensity);
				VINZIJsonToStructInst.VINZIstruct_Float(LightObject, "vLightRotation", LightStruct.VLightRotation);

				VINZIJsonToStructInst.VINZIstruct_Int32(LightObject, "vLightTemperature", LightStruct.VLightTemperature);
				VINZIJsonToStructInst.VINZIstruct_Int32(LightObject, "vLightScissorsSegments", LightStruct.VLightScissorsSegments);
				VINZIJsonToStructInst.VINZIstruct_Int32(LightObject, "vTargetID", LightStruct.VTargetID);

				VINZIJsonToStructInst.VINZIstruct_Bool(LightObject, "vLightTemperatureBool", LightStruct.VLightTemperatureBool);
				VINZIJsonToStructInst.VINZIstruct_Bool(LightObject, "vLightDifuserBool", LightStruct.VLightDifuserBool);
				VINZIJsonToStructInst.VINZIstruct_Bool(LightObject, "vLightGridBool", LightStruct.VLightGridBool);
				VINZIJsonToStructInst.VINZIstruct_Bool(LightObject, "vHideMesh", LightStruct.VHideMesh);

				VINZIJsonToStructInst.VINZIstruct_LinearColor(LightObject, "vLightTint", LightStruct.VLightTint);

				VINZIJsonToStructInst.VINZIstruct_Enum<EVLightTypeMS>(LightObject, "vLightType", LightStruct.VLightType);
				VINZIJsonToStructInst.VINZIstruct_Enum<EVLightUnitsMS>(LightObject, "vLightUnits", LightStruct.VLightUnits);
				VINZIJsonToStructInst.VINZIstruct_Enum<EVLightSupportMS>(LightObject, "vLightSupport", LightStruct.VLightSupport);

				VINZIJsonToStructInst.VINZIstruct_String(LightObject, "vTargetName", LightStruct.VTargetName);


				StudioStruct.Lights.Add(LightStruct);

			}

			TArray<TSharedPtr<FJsonValue>> TargetsArray = JsonObject->GetArrayField("targets");
			for (const TSharedPtr<FJsonValue>& TargetValue : TargetsArray)
			{
				FSMetaShoot_Target TargetStruct;

				TSharedPtr<FJsonObject> TargetObject = TargetValue->AsObject();

				VINZIJsonToStructInst.VINZIstruct_Transform(TargetObject, "vTransform", TargetStruct.VTransform);

				VINZIJsonToStructInst.VINZIstruct_LinearColor(TargetObject, "vTint", TargetStruct.VTint);

				VINZIJsonToStructInst.VINZIstruct_String(TargetObject, "vTargetName", TargetStruct.VTargetName);

				VINZIJsonToStructInst.VINZIstruct_Int32(TargetObject, "vTargetID", TargetStruct.VTargetID);


				StudioStruct.Targets.Add(TargetStruct);

			}

			TArray<TSharedPtr<FJsonValue>> LightBanksArray = JsonObject->GetArrayField("lightBanks");
			for (const TSharedPtr<FJsonValue>& LightBankValue : LightBanksArray)
			{
				FSMetaShoot_LightBank LightBankStruct;

				TSharedPtr<FJsonObject> LightBankObject = LightBankValue->AsObject();

				VINZIJsonToStructInst.VINZIstruct_Transform(LightBankObject, "vTransform", LightBankStruct.VTransform);

				VINZIJsonToStructInst.VINZIstruct_Float(LightBankObject, "vLightIntensity", LightBankStruct.VLightIntensity);

				VINZIJsonToStructInst.VINZIstruct_Int32(LightBankObject, "vLightTemperature", LightBankStruct.VLightTemperature);
				VINZIJsonToStructInst.VINZIstruct_Int32(LightBankObject, "vTargetID", LightBankStruct.VTargetID);

				VINZIJsonToStructInst.VINZIstruct_Bool(LightBankObject, "vLightTemperatureBool", LightBankStruct.VLightTemperatureBool);
				VINZIJsonToStructInst.VINZIstruct_Bool(LightBankObject, "vHideMesh", LightBankStruct.VHideMesh);

				VINZIJsonToStructInst.VINZIstruct_LinearColor(LightBankObject, "vLightTint", LightBankStruct.VLightTint);

				VINZIJsonToStructInst.VINZIstruct_String(LightBankObject, "vTargetName", LightBankStruct.VTargetName);


				StudioStruct.LightBanks.Add(LightBankStruct);

			}

			TArray<TSharedPtr<FJsonValue>> DSLRArray = JsonObject->GetArrayField("dSLRs");
			for (const TSharedPtr<FJsonValue>& DSLRValue : DSLRArray)
			{
				FSMetaShoot_DSLR DSLRStruct;

				TSharedPtr<FJsonObject> DSLRObject = DSLRValue->AsObject();

				VINZIJsonToStructInst.VINZIstruct_Transform(DSLRObject, "vTransform", DSLRStruct.VTransform);

				VINZIJsonToStructInst.VINZIstruct_Float(DSLRObject, "vCameraMeshScale", DSLRStruct.VCameraMeshScale);

				VINZIJsonToStructInst.VINZIstruct_Int32(DSLRObject, "vTargetID", DSLRStruct.VTargetID);

				VINZIJsonToStructInst.VINZIstruct_Bool(DSLRObject, "vCameraMeshHidden", DSLRStruct.VCameraMeshHidden);

				VINZIJsonToStructInst.VINZIstruct_String(DSLRObject, "vTargetName", DSLRStruct.VTargetName);


				StudioStruct.DSLRs.Add(DSLRStruct);

			}

			TArray<TSharedPtr<FJsonValue>> TurntableArray = JsonObject->GetArrayField("turntables");
			for (const TSharedPtr<FJsonValue>& TurntableValue : TurntableArray)
			{
				FSMetaShoot_Turntable TurntableStruct;

				TSharedPtr<FJsonObject> TurntableObject = TurntableValue->AsObject();

				VINZIJsonToStructInst.VINZIstruct_Transform(TurntableObject, "vTransform", TurntableStruct.VTransform);
				VINZIJsonToStructInst.VINZIstruct_Transform(TurntableObject, "vTransformChild", TurntableStruct.VTransformChild);

				VINZIJsonToStructInst.VINZIstruct_Float(TurntableObject, "vDegrees", TurntableStruct.VDegrees);
				VINZIJsonToStructInst.VINZIstruct_Float(TurntableObject, "vRotationTime", TurntableStruct.VRotationTime);
				VINZIJsonToStructInst.VINZIstruct_Float(TurntableObject, "vDelay", TurntableStruct.VDelay);
				VINZIJsonToStructInst.VINZIstruct_Float(TurntableObject, "vBaseScale", TurntableStruct.VBaseScale);

				VINZIJsonToStructInst.VINZIstruct_Bool(TurntableObject, "vRotate", TurntableStruct.VRotate);
				VINZIJsonToStructInst.VINZIstruct_Bool(TurntableObject, "vLoop", TurntableStruct.VLoop);
				VINZIJsonToStructInst.VINZIstruct_Bool(TurntableObject, "vClockwise", TurntableStruct.VClockwise);
				VINZIJsonToStructInst.VINZIstruct_Bool(TurntableObject, "vHideBase", TurntableStruct.VHideBase);
				VINZIJsonToStructInst.VINZIstruct_Bool(TurntableObject, "vPreviewZ", TurntableStruct.VPreviewZ);

				StudioStruct.Turntables.Add(TurntableStruct);

			}

			TArray<TSharedPtr<FJsonValue>> RailArray = JsonObject->GetArrayField("rails");
			for (const TSharedPtr<FJsonValue>& RailValue : RailArray)
			{
				FSMetaShoot_Rail RailStruct;

				TSharedPtr<FJsonObject> RailObject = RailValue->AsObject();

				VINZIJsonToStructInst.VINZIstruct_Transform(RailObject, "vTransform", RailStruct.VTransform);

				VINZIJsonToStructInst.VINZIstruct_Float(RailObject, "vSeparation", RailStruct.VSeparation);
				VINZIJsonToStructInst.VINZIstruct_Float(RailObject, "vLength", RailStruct.VLength);

				StudioStruct.Rails.Add(RailStruct);

			}
		}
	}
}

/*
#if WITH_EDITOR
void AMetaShoot_Studio::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_Studio, PresetName)) {
		if (PresetName != "")
		{
			UpdateFullStudio();
		}
		else
		{
		}
	}
}
#endif
*/