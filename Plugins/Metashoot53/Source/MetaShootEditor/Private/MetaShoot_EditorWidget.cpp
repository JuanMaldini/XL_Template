// Copyright 2023, VINZI Studio S.L. All rights reserved


#include "MetaShoot_EditorWidget.h"

#include "VINZI_JsonToStruct.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "JsonObjectConverter.h"
#include "JsonUtilities.h"

#include "Misc/DateTime.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMisc.h"
#include "HAL/FileManagerGeneric.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/FileManager.h"







//#define DEBUG_MSG(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}

UMetaShoot_EditorWidget::UMetaShoot_EditorWidget()
{
	UMetaShoot_EditorWidget::checkRayTracing();
}

UMetaShoot_EditorWidget::~UMetaShoot_EditorWidget()
{
}



//void UMetaShoot_EditorWidget::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("OK"));
//}

void UMetaShoot_EditorWidget::getViewPortCameraPosLoc()
{

	FViewport* activeViewport = GEditor->GetActiveViewport();
	FEditorViewportClient* editorViewClient = (activeViewport != nullptr) ? (FEditorViewportClient*)activeViewport->GetClient() : nullptr;
	if (editorViewClient)
	{
		viewPos = editorViewClient->GetViewLocation();
		viewRot = editorViewClient->GetViewRotation();
	}
}

void UMetaShoot_EditorWidget::checkRayTracing() {
	/*if (GSupportsRayTracing)
	{
		UE_LOG(LogTemp, Log, TEXT("Ray tracing is enabled in the project"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Ray tracing is not enabled in the project"));
	}*/
}



void UMetaShoot_EditorWidget::GetSample()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UMetaShoot_EditorWidget::OnResponseReceivedSample);
	Request->SetURL("https://jsonplaceholder.typicode.com/posts/1");
	Request->SetVerb("GET");

	Request->ProcessRequest();
}

void UMetaShoot_EditorWidget::PostSample()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("title", "foo");

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UMetaShoot_EditorWidget::OnResponseReceivedSample);
	Request->SetURL("https://jsonplaceholder.typicode.com/posts");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);

	Request->ProcessRequest();
}


void UMetaShoot_EditorWidget::OnResponseReceivedSample(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	UE_LOG(LogTemp, Display, TEXT("Response %s"), *Response->GetContentAsString());
	UE_LOG(LogTemp, Display, TEXT("Title: %s"), *ResponseObj->GetStringField("title"));
}









FString keyPath = FPaths::ConvertRelativePathToFull(FPaths::RootDir()) + TEXT("Engine/Plugins/VINZI/MetaShoot/log.txt");

FString GetPluginFolderPath(const FString& PluginName)
{
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(PluginName);

	if (Plugin.IsValid())
	{
		FString PluginBaseDir = Plugin->GetBaseDir();
		return FPaths::ConvertRelativePathToFull(PluginBaseDir);
	}

	return FString();
}

FString MetaShootPath = GetPluginFolderPath(TEXT("MetaShoot"));
FString MetaShootEnginePath = FPaths::ConvertRelativePathToFull(FPaths::RootDir()) + TEXT("Engine/Plugins/VINZI/MetaShoot");
FString ProjectPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());


FTimerHandle UpdateLastCheckTimerHandle;
FTimerHandle LoggedOutTimerHandle;

void UMetaShoot_EditorWidget::printRequestResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
{
	UE_LOG(LogTemp, Display, TEXT("Response %s"), *Response->GetContentAsString());
}

void UMetaShoot_EditorWidget::printLogNews(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
{
	FString MSLogNewsResponse = Response->GetContentAsString();
	FString LogNewsBool, LogNewsText;
	MSLogNewsResponse.Split(TEXT("_"), &LogNewsBool, &LogNewsText);

	if (LogNewsBool == "true")
	{
		BShowNewsLog = true;
	}
	else
	{
		BShowNewsLog = false;
	}
	
	VNewsLog = LogNewsText;

	//UE_LOG(LogTemp, Display, TEXT("Response %s"), *VNewsLog);

	UMetaShoot_EditorWidget::UpdateNewsLog();
}

void UMetaShoot_EditorWidget::checkLog()
{

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*keyPath))
	{
		//if local log file exists

		//Load log txt
		FString FileData = "";
		FFileHelper::LoadFileToString(FileData, *keyPath);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(FileData);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			FString FLocalEmail = JsonObject->GetStringField("email");
			FString FLocalSession = JsonObject->GetStringField("session");

			Vemail = FLocalEmail;

			FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

			TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
			RequestObj->SetStringField("email", FLocalEmail);
			RequestObj->SetStringField("session", FLocalSession);

			FDateTime currentTime = FDateTime::UtcNow();
			FString currentTimeString = currentTime.ToString().Replace(TEXT("."), TEXT(""));
			RequestObj->SetStringField("currentTime", currentTimeString);

			FString RequestBody;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
			FJsonSerializer::Serialize(RequestObj, Writer);

			Request->OnProcessRequestComplete().BindUObject(this, &UMetaShoot_EditorWidget::loginChecked);
			Request->SetURL("https://vinzi.xyz/MetaShoot/license/checkLog.php");
			Request->SetVerb("POST");
			Request->SetHeader("Content-Type", "application/json");
			Request->SetContentAsString(RequestBody);

			Request->ProcessRequest();
		}

		//UMetaShoot_EditorWidget::checkSession();

	}
	else
	{
		//if local log file doesn't exist

		FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

		TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();

		FString RequestBody;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
		FJsonSerializer::Serialize(RequestObj, Writer);

		Request->OnProcessRequestComplete().BindUObject(this, &UMetaShoot_EditorWidget::loginChecked);
		Request->SetURL("https://vinzi.xyz/MetaShoot/license/checkLog.php");
		Request->SetVerb("POST");
		Request->SetHeader("Content-Type", "application/json");
		Request->SetContentAsString(RequestBody);

		Request->ProcessRequest();



		/*BMSActive = false;
		VphpResponse = TEXT("");
		UMetaShoot_EditorWidget::LoggedEvent();*/
	}

}

void UMetaShoot_EditorWidget::authenticate()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("email", Vemail);
	RequestObj->SetStringField("password", Vpassword);

	//Get current UTC universal date - no daylight savings apply
	FDateTime currentTime = FDateTime::UtcNow();
	FString currentTimeString = currentTime.ToString().Replace(TEXT("."), TEXT(""));

	RequestObj->SetStringField("currentTime", currentTimeString);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UMetaShoot_EditorWidget::loginChecked);
	Request->SetURL("https://vinzi.xyz/MetaShoot/license/authenticate.php");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);

	Request->ProcessRequest();
}

void UMetaShoot_EditorWidget::loginChecked(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccesfully)
{
	FString MSRequestResponse = Response->GetContentAsString();

	FString responseLogged, responseCase;
	MSRequestResponse.Split(TEXT("_"), &responseLogged, &responseCase);

	GetWorld()->GetTimerManager().ClearTimer(LoggedOutTimerHandle);

	if (responseLogged == "LoggedIn") {
		BMSActive = true;
		VphpResponse = TEXT("");
		UMetaShoot_EditorWidget::updateLog(responseCase);
	}
	else if(responseLogged == "LoggedOut") {
		BMSActive = false;
		VphpResponse = responseCase;
		UMetaShoot_EditorWidget::loggedOutMessage();
		GetWorld()->GetTimerManager().SetTimer(LoggedOutTimerHandle, this, &UMetaShoot_EditorWidget::loggedOutMessage, 16.0f, true);
	}
	if (responseLogged == "") {
		//OFFLINE MODE
		BMSActive = true;
		VphpResponse = TEXT("");
		Vemail = TEXT("Offline");
	}

	UE_LOG(LogTemp, Display, TEXT("Logged response: %s"), *responseLogged);
	UE_LOG(LogTemp, Display, TEXT("Case response: %s"), *responseCase);

	UMetaShoot_EditorWidget::LoggedEvent();
	UMetaShoot_EditorWidget::applyLicenseToMetaShootActors(responseLogged);
}

void UMetaShoot_EditorWidget::updateLog(FString Case)
{

	//Get License Info
	FString licenseType = "";
	FString licenseNotes = "";
	//FString licensePath = FPaths::ConvertRelativePathToFull(FPaths::RootDir()) + TEXT("Engine/Plugins/Marketplace/MetaShoot/Source/License.json");

	FString licensePath = MetaShootPath + TEXT("/Source/License.json");


	/*if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*licensePath))
	{
		licensePath = FPaths::ConvertRelativePathToFull(FPaths::RootDir()) + TEXT("Engine/Plugins/MetaShoot/Source/License.json");
	}

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*licensePath))
	{
		licensePath = FPaths::ProjectPluginsDir() + "MetaShoot/Source/License.json";
	}*/

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*licensePath))
	{
		FString FileData = "";
		FFileHelper::LoadFileToString(FileData, *licensePath);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(FileData);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			licenseType = JsonObject->GetStringField("type");
			licenseNotes = JsonObject->GetStringField("notes");
		}
	}

	//Get email and session variables
	FString updatedEmail;

	if (Case == TEXT("checkLog")) {
		//read local log, get email
		FString FileData = "";
		FFileHelper::LoadFileToString(FileData, *keyPath);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(FileData);

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			FString Femail = JsonObject->GetStringField("email");
			FString Fsession = JsonObject->GetStringField("session");

			updatedEmail = Femail;
		}
	}

	if (Case == TEXT("authenticate")) {
		//get email from UI form
		updatedEmail = Vemail;
	}

	//Get current UTC universal date - no daylight savings apply
	FDateTime currentTime = FDateTime::UtcNow();
	FString currentTimeString = currentTime.ToString().Replace(TEXT("."), TEXT(""));

	//Get plugin and Engine version
	FString UEVersion = "";
	FString PluginVersion = "";
	FString UEPlatform = "";

	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("MetaShoot"));

	if (Plugin.IsValid())
	{
		//UEVersion = Plugin->GetDescriptor().EngineVersion;
		PluginVersion = Plugin->GetDescriptor().VersionName;

		MSVersion = PluginVersion;
	}

	FEngineVersion EngineVersion = FEngineVersion::Current();
	int Major = EngineVersion.GetMajor();
	int Minor = EngineVersion.GetMinor();
	int Patch = EngineVersion.GetPatch();
	int Changelist = EngineVersion.GetChangelist();

	UEVersion = FString::FromInt(Major) + "." + FString::FromInt(Minor) + "." + FString::FromInt(Patch) + "_" + FString::FromInt(Changelist);

#if PLATFORM_WINDOWS
	UEPlatform = "Windows";
#elif PLATFORM_MAC
	UEPlatform = "Mac";
#else
	UEPlatform = "Unknown";
#endif

	//Update local log
	TSharedRef<FJsonObject> writeJsonObj = MakeShared<FJsonObject>();
	writeJsonObj->SetStringField("email", updatedEmail);
	writeJsonObj->SetStringField("session", currentTimeString);

	FString writeBody;
	TSharedRef<TJsonWriter<>> writeWriter = TJsonWriterFactory<>::Create(&writeBody);
	FJsonSerializer::Serialize(writeJsonObj, writeWriter);

	FString FileContent = writeBody;
	FFileHelper::SaveStringToFile(FileContent, *keyPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
	//Append text to file instead of replacing it
	//FFileHelper::SaveStringToFile(FileContent, *keyPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);


	//Update server log

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("email", updatedEmail);
	RequestObj->SetStringField("session", currentTimeString);
	RequestObj->SetStringField("ue_version", UEVersion);
	RequestObj->SetStringField("ms_version", PluginVersion);
	RequestObj->SetStringField("ue_platform", UEPlatform);
	RequestObj->SetStringField("license_type", licenseType);
	RequestObj->SetStringField("license_notes", licenseNotes);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UMetaShoot_EditorWidget::printLogNews);
	Request->SetURL("https://vinzi.xyz/MetaShoot/license/updateLog.php");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);

	Request->ProcessRequest();

	UMetaShoot_EditorWidget::updateLastCheck();
	// Start the timer to call updateLastCheck every 25 seconds
	GetWorld()->GetTimerManager().SetTimer(UpdateLastCheckTimerHandle, this, &UMetaShoot_EditorWidget::updateLastCheck, 25.0f, true);

}

void UMetaShoot_EditorWidget::logout()
{
	FString updatedEmail;

	//read local log, get email
	FString FileData = "";
	FFileHelper::LoadFileToString(FileData, *keyPath);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(FileData);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		FString Femail = JsonObject->GetStringField("email");
		FString Fsession = JsonObject->GetStringField("session");

		updatedEmail = Femail;
	}

	//Get current UTC universal date - no daylight savings apply
	FDateTime currentTime = FDateTime::UtcNow();
	FString currentTimeString = currentTime.ToString().Replace(TEXT("."), TEXT(""));

	//Update local log
	TSharedRef<FJsonObject> writeJsonObj = MakeShared<FJsonObject>();
	writeJsonObj->SetStringField("email", updatedEmail);
	writeJsonObj->SetStringField("session", currentTimeString);

	FString writeBody;
	TSharedRef<TJsonWriter<>> writeWriter = TJsonWriterFactory<>::Create(&writeBody);
	FJsonSerializer::Serialize(writeJsonObj, writeWriter);

	FString FileContent = writeBody;
	FFileHelper::SaveStringToFile(FileContent, *keyPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);


	//Get Logout php
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UMetaShoot_EditorWidget::loginChecked);
	Request->SetURL("https://vinzi.xyz/MetaShoot/license/logout.php");
	Request->SetVerb("GET");

	Request->ProcessRequest();

	// Stop the timer
	GetWorld()->GetTimerManager().ClearTimer(UpdateLastCheckTimerHandle);
}


void UMetaShoot_EditorWidget::updateLastCheck()
{
	//Get email and session variables
	FString updatedEmail = Vemail;

	//Get current UTC universal date - no daylight savings apply
	FDateTime currentTime = FDateTime::UtcNow();
	FString currentTimeString = currentTime.ToString().Replace(TEXT("."), TEXT(""));

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("email", updatedEmail);
	RequestObj->SetStringField("lastCheck", currentTimeString);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	//Request->OnProcessRequestComplete().BindUObject(this, &UMetaShoot_EditorWidget::printRequestResponse);
	Request->SetURL("https://vinzi.xyz/MetaShoot/license/updateLastCheck.php");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);

	Request->ProcessRequest();
}



void UMetaShoot_EditorWidget::applyLicenseToMetaShootActors(FString Case)
{
	
	if (Case == "LoggedIn" || Case == "") {
		//Case "" is Offline Mode
		for (TObjectIterator<AMetaShoot_SoftboxMaster> Itr; Itr; ++Itr)
		{
			AMetaShoot_SoftboxMaster* MyObject = *Itr;
			//UE_LOG(LogTemp, Display, TEXT("MyObject: %s"), *MyObject->GetName());

			MyObject->BMSAssetActive = true;

			TArray<UActorComponent*> Components;
			MyObject->GetComponents(Components);
			for (UActorComponent* Component : Components)
			{
				if (Component->IsA<UStaticMeshComponent>()) // check if the component is a Static Mesh Component
				{
					UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component);
					StaticMesh->SetVisibility(true);
				}
			}
			
			MyObject->UpdateAll(true);
		}
		for (TObjectIterator<AMetaShoot_OverheadLightBank> Itr; Itr; ++Itr)
		{
			AMetaShoot_OverheadLightBank* MyObject = *Itr;
			//UE_LOG(LogTemp, Display, TEXT("MyObject: %s"), *MyObject->GetName());

			MyObject->BMSAssetActive = true;

			TArray<UActorComponent*> Components;
			MyObject->GetComponents(Components);
			for (UActorComponent* Component : Components)
			{
				if (Component->IsA<UStaticMeshComponent>()) // check if the component is a Static Mesh Component
				{
					UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component);
					StaticMesh->SetVisibility(true);
				}
			}

			MyObject->UpdateAll();
		}
		for (TObjectIterator<AMetaShoot_Cyclorama> Itr; Itr; ++Itr)
		{
			AMetaShoot_Cyclorama* MyObject = *Itr;
			//UE_LOG(LogTemp, Display, TEXT("MyObject: %s"), *MyObject->GetName());
			MyObject->BMSAssetActive = true;

			TArray<UActorComponent*> Components;
			MyObject->GetComponents(Components);
			for (UActorComponent* Component : Components)
			{
				if (Component->IsA<UStaticMeshComponent>()) // check if the component is a Static Mesh Component
				{
					UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component);
					StaticMesh->SetVisibility(true);
				}
			}

			MyObject->UpdateCyclorama();
		}
		/*for (TObjectIterator<AMetaShoot_DSLRCamera> Itr; Itr; ++Itr)
		{
			AMetaShoot_DSLRCamera* MyObject = *Itr;
			MyObject->BMSAssetActive = true;
		}*/
	}
	else if (Case == "LoggedOut") {
		for (TObjectIterator<AMetaShoot_SoftboxMaster> Itr; Itr; ++Itr)
		{
			AMetaShoot_SoftboxMaster* MyObject = *Itr;
			MyObject->BMSAssetActive = false;

			MyObject->RectLightComponent->SetVisibility(false);
			MyObject->PointLightComponent->SetVisibility(false);
			MyObject->SpotLightComponent->SetVisibility(false);

			TArray<UActorComponent*> Components;
			MyObject->GetComponents(Components);
			for (UActorComponent* Component : Components)
			{
				if (Component->IsA<UStaticMeshComponent>()) // check if the component is a Static Mesh Component
				{
					UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component);
					StaticMesh->SetVisibility(false);
				}
			}

			MyObject->UpdateAll(true);
		}
		for (TObjectIterator<AMetaShoot_OverheadLightBank> Itr; Itr; ++Itr)
		{
			AMetaShoot_OverheadLightBank* MyObject = *Itr;
			MyObject->BMSAssetActive = false;

			MyObject->RectLightComponent->SetVisibility(false);

			TArray<UActorComponent*> Components;
			MyObject->GetComponents(Components);
			for (UActorComponent* Component : Components)
			{
				if (Component->IsA<UStaticMeshComponent>()) // check if the component is a Static Mesh Component
				{
					UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component);
					StaticMesh->SetVisibility(false);
				}
			}

			MyObject->UpdateAll();
		}
		for (TObjectIterator<AMetaShoot_Cyclorama> Itr; Itr; ++Itr)
		{
			AMetaShoot_Cyclorama* MyObject = *Itr;
			//UE_LOG(LogTemp, Display, TEXT("MyObject: %s"), *MyObject->GetName());
			MyObject->BMSAssetActive = false;

			TArray<UActorComponent*> Components;
			MyObject->GetComponents(Components);
			for (UActorComponent* Component : Components)
			{
				if (Component->IsA<UStaticMeshComponent>()) // check if the component is a Static Mesh Component
				{
					UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component);
					StaticMesh->SetVisibility(false);
				}
			}

			MyObject->UpdateCyclorama();
		}
		/*for (TObjectIterator<AMetaShoot_DSLRCamera> Itr; Itr; ++Itr)
		{
			AMetaShoot_DSLRCamera* MyObject = *Itr;
			MyObject->BMSAssetActive = false;
		}*/
	}

}

void UMetaShoot_EditorWidget::loggedOutMessage()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Yellow, TEXT("Please login to MetaShoot to access its interface and activate its assets. You can find it in Window/MetaShoot"));
}



void UMetaShoot_EditorWidget::MSRender()
{
	/*UMovieScene* MSMovieScene = MSLevelSequence->GetMovieScene();

	FFrameRate FrameRate = MSMovieScene->GetTickResolution();

	TRange<FFrameNumber> MyFrameRange = MSMovieScene->GetPlaybackRange();*/

	/*
	FFrameNumber NewLowerBound = 10;
	FFrameNumber NewUpperBound = 20;
	MyFrameRange.SetLowerBoundValue(NewLowerBound);
	MyFrameRange.SetUpperBoundValue(NewUpperBound);

	MSMovieScene->SetPlaybackRange(MyFrameRange);
	MSMovieScene->MarkAsChanged();
	*/


	/*for (int i = 0; i < MSMovieScene->GetMasterTracks().Num(); i++) {
		for (int j = 0; j < MSMovieScene->GetMasterTracks()[i]->GetAllSections().Num(); j++) {
			MSMovieScene->GetMasterTracks()[i]->RemoveSectionAt(j);
			//MSMovieScene->GetMasterTracks()[i]->RemoveSection(MSMovieScene->GetMasterTracks()[i]->GetAllSections()[j]);
		}

		//UMovieSceneTrack* test01 = MSMovieScene->GetMasterTracks()[i];

		MSMovieScene->RemoveMasterTrack(*MSMovieScene->GetMasterTracks()[i]);
	}

	for (int i = 0; i < MSMovieScene->GetPossessableCount(); i++) {
		MSMovieScene->RemovePossessable(MSMovieScene->GetPossessable(i).GetGuid());
	}



	//UMovieSceneCameraCutTrack* NewTrack = NewObject<UMovieSceneCameraCutTrack>(MSMovieScene, "CameraCutTrack");
	//UMovieSceneTrack* NewTrack = NewObject<UMovieSceneTrack>(MSMovieScene, "CameraCutTrack");

	//UMovieSceneCameraCutTrack* testTrack = MSMovieScene->AddMasterTrack<UMovieSceneCameraCutTrack>()->AddSection();


	MSMovieScene->MarkAsChanged();*/

}



//FString presetsFullPath = FPaths::ConvertRelativePathToFull(FPaths::RootDir()) + TEXT("Engine/Plugins/VINZI/MetaShoot/presets.json");

TArray<FString> UMetaShoot_EditorWidget::PresetsRefreshList()
{
	// Copy plugin folder MetaShoot presets to the Engine folder

	FString SourceFolderPath = MetaShootPath + TEXT("/Source/Presets/");
	FString DestinationFolder = MetaShootEnginePath + TEXT("/Presets/MS/");

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// Create a file list
	TArray<FString> FileList;

	// Iterate through the source folder to find all files
	IFileManager::Get().FindFilesRecursive(FileList, *SourceFolderPath, TEXT("*.*"), true, false);

	// Make sure the destination folder exists, create it if not
	if (!PlatformFile.DirectoryExists(*DestinationFolder))
	{
		PlatformFile.CreateDirectoryTree(*DestinationFolder);
	}

	// Copy each file found in the source folder
	for (const FString& SourceFilePath : FileList)
	{
		FString RelativePath = SourceFilePath;
		FPaths::MakePathRelativeTo(RelativePath, *SourceFolderPath);

		FString DestinationFilePath = FPaths::Combine(DestinationFolder, RelativePath);

		// Check if the file already exists in the destination folder
		//if (!PlatformFile.FileExists(*DestinationFilePath))
		//{
			FString DestinationFileDirectory = FPaths::GetPath(DestinationFilePath);
			if (!PlatformFile.DirectoryExists(*DestinationFileDirectory))
			{
				PlatformFile.CreateDirectoryTree(*DestinationFileDirectory);
			}

			PlatformFile.CopyFile(*DestinationFilePath, *SourceFilePath, EPlatformFileRead::AllowWrite, EPlatformFileWrite::AllowRead);
		//}
	}


	//Find presets
	
	IFileManager& FileManager = IFileManager::Get();

	TArray<FString> JsonFiles;

	FString FolderPath = MetaShootEnginePath + TEXT("/Presets/");
	FString FilePattern = FolderPath / TEXT("*.vnzms");
	FileManager.FindFiles(JsonFiles, *FilePattern, /*Files=*/true, /*Directories=*/false);

	
	TArray<FString> JsonFilesLocal;

	FString FolderPathLocal = ProjectPath + TEXT("Source/MetaShoot/Presets/");
	FString FilePatternLocal = FolderPathLocal / TEXT("*.vnzms");
	FileManager.FindFiles(JsonFilesLocal, *FilePatternLocal, /*Files=*/true, /*Directories=*/false);

	
	JsonFiles.Append(JsonFilesLocal);


	// Remove the ".vnzms" extension from the file names
	for (FString& FileName : JsonFiles)
	{
		FileName = FPaths::GetBaseFilename(FileName);
	}


	return JsonFiles;
}


void UMetaShoot_EditorWidget::PresetsSaveStudio(const FSMetaShoot_Studio& StudioStruct)
{
	if (VSaveLocal)
	{
		presetsFullPath = ProjectPath + TEXT("Source/MetaShoot/Presets/") + NewPresetName + TEXT(".vnzms");
	}
	else
	{
		presetsFullPath = MetaShootEnginePath + TEXT("/Presets/") + NewPresetName + TEXT(".vnzms");
	}
	

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	FJsonObjectConverter::UStructToJsonObject(FSMetaShoot_Studio::StaticStruct(), &StudioStruct, JsonObject.ToSharedRef(), 0, 0);

	FString JsonString;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	if (FPaths::DirectoryExists(MetaShootEnginePath))
	{
		FFileHelper::SaveStringToFile(JsonString, *presetsFullPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
	}
}

void UMetaShoot_EditorWidget::PresetsDeleteStudio()
{
	
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	presetsFullPath = MetaShootEnginePath + TEXT("/Presets/") + VPreset + TEXT(".vnzms");

	if (PlatformFile.FileExists(*presetsFullPath))
	{
		UE_LOG(LogTemp, Log, TEXT("Preset"));
		if (PlatformFile.DeleteFile(*presetsFullPath))
		{
			UE_LOG(LogTemp, Log, TEXT("Preset deleted successfully"));
		}
	}
	else {
		presetsFullPath = ProjectPath + TEXT("Source/MetaShoot/Presets/") + VPreset + TEXT(".vnzms");

		if (PlatformFile.FileExists(*presetsFullPath))
		{
			UE_LOG(LogTemp, Log, TEXT("Preset"));
			if (PlatformFile.DeleteFile(*presetsFullPath))
			{
				UE_LOG(LogTemp, Log, TEXT("Preset deleted successfully"));
			}
		}
	}
}




VINZI_JsonToStruct VINZIJsonToStructInst;

//OBSOLETE! THIS FUNCTION IS IN THE STUDIO ACTOR
void UMetaShoot_EditorWidget::PresetsLoadStudio(FSMetaShoot_Studio& StudioStruct)
{
	
}



TSubclassOf<AMetaShoot_Preset> UMetaShoot_EditorWidget::CheckMSPresetClass(UObject* BlueprintAsset)
{
	TSubclassOf<AMetaShoot_Preset> ResultingClass = nullptr;

	// Check if the asset is a Blueprint
	if (UBlueprint* Blueprint = Cast<UBlueprint>(BlueprintAsset))
	{
		// Get the generated class of the Blueprint
		UClass* BlueprintGeneratedClass = Blueprint->GeneratedClass.Get();
		if (BlueprintGeneratedClass)
		{
			// Get the native parent class
			UClass* CurrentClass = BlueprintGeneratedClass;
			while (CurrentClass)
			{
				if (CurrentClass->HasAnyClassFlags(CLASS_Native))
				{
					if (CurrentClass->IsChildOf(AMetaShoot_Preset::StaticClass()))
					{
						// Return the input class itself when the parent class is AMetaShoot_Preset
						ResultingClass = BlueprintGeneratedClass;
					}
					break;
				}
				CurrentClass = CurrentClass->GetSuperClass();
			}
		}
	}

	return ResultingClass;
}

TSubclassOf<AActor> UMetaShoot_EditorWidget::CheckActorClass(UObject* BlueprintAsset)
{
	TSubclassOf<AActor> ResultingClass = nullptr;

	// Check if the asset is a Blueprint
	if (UBlueprint* Blueprint = Cast<UBlueprint>(BlueprintAsset))
	{
		// Get the generated class of the Blueprint
		UClass* BlueprintGeneratedClass = Blueprint->GeneratedClass.Get();
		if (BlueprintGeneratedClass)
		{
			// Get the native parent class
			UClass* CurrentClass = BlueprintGeneratedClass;
			while (CurrentClass)
			{
				if (CurrentClass->HasAnyClassFlags(CLASS_Native))
				{
					if (CurrentClass->IsChildOf(AActor::StaticClass()))
					{
						// Return the input class itself when the parent class is a child of AActor
						ResultingClass = BlueprintGeneratedClass;
					}
					break;
				}
				CurrentClass = CurrentClass->GetSuperClass();
			}
		}
	}

	return ResultingClass;
}


bool UMetaShoot_EditorWidget::IsNewerVersion(FString version1, FString version2)
{
	// Split the version strings into arrays
	TArray<FString> v1, v2;
	version1.ParseIntoArray(v1, TEXT("."));
	version2.ParseIntoArray(v2, TEXT("."));

	// Get the maximum size of both arrays
	int32 max_size = FMath::Max(v1.Num(), v2.Num());

	// Compare each part of the version numbers
	for (int32 i = 0; i < max_size; i++)
	{
		// If we have reached the end of either array, add "0"
		FString part1 = (i < v1.Num()) ? v1[i] : FString("0");
		FString part2 = (i < v2.Num()) ? v2[i] : FString("0");

		// Convert to integers for comparison
		int32 num1 = FCString::Atoi(*part1);
		int32 num2 = FCString::Atoi(*part2);

		if (num1 < num2)
			return false;
		else if (num1 > num2)
			return true;
	}

	// If we made it here, the versions are equal
	return false;
}