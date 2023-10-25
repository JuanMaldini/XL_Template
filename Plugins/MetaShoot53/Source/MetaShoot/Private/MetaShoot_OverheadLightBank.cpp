// Copyright 2023, VINZI Studio S.L. All rights reserved


#include "MetaShoot_OverheadLightBank.h"

#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMetaShoot_OverheadLightBank::AMetaShoot_OverheadLightBank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LightBank_Root = CreateDefaultSubobject<USceneComponent>(FName("LightBank Root"));
	this->SetRootComponent(LightBank_Root);

	RectLightComponent = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLight"));
	RectLightComponent->SetupAttachment(LightBank_Root);
	RectLightComponent->SetAttenuationRadius(1000);
	RectLightComponent->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	LightDiffuser = CreateDefaultSubobject<UStaticMeshComponent>(FName("Light Diffuser"));
	LightDiffuser->SetupAttachment(LightBank_Root);
	LightDiffuser->SetRelativeLocation(FVector(0.0f, 0.0f, 7.0f));

	LightBox = CreateDefaultSubobject<UStaticMeshComponent>(FName("LightBox"));
	LightBox->SetupAttachment(LightDiffuser);

	LightBoxFrame = CreateDefaultSubobject<UStaticMeshComponent>(FName("LightBox Frame"));
	LightBoxFrame->SetupAttachment(LightBox);

	SpotlightMesh00 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Spotlight 00"));
	SpotlightMesh00->SetupAttachment(LightBoxFrame);
	SpotlightMesh01 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Spotlight 01"));
	SpotlightMesh01->SetupAttachment(LightBoxFrame);
	SpotlightMesh02 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Spotlight 02"));
	SpotlightMesh02->SetupAttachment(LightBoxFrame);
	SpotlightMesh03 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Spotlight 03"));
	SpotlightMesh03->SetupAttachment(LightBoxFrame);
	SpotlightMesh04 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Spotlight 04"));
	SpotlightMesh04->SetupAttachment(LightBoxFrame);

	SpotlightMesh00->SetRelativeLocation(FVector(0.0f, 0.0f, 68.0f));
	SpotlightMesh01->SetRelativeLocation(FVector(88.0f, 44.0f, 68.0f));
	SpotlightMesh02->SetRelativeLocation(FVector(88.0f, -44.0f, 68.0f));
	SpotlightMesh03->SetRelativeLocation(FVector(-88.0f, 44.0f, 68.0f));
	SpotlightMesh04->SetRelativeLocation(FVector(-88.0f, -44.0f, 68.0f));

	SpotlightMesh00->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpotlightMesh01->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpotlightMesh02->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpotlightMesh03->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpotlightMesh04->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	SpotlightHingeMesh00 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Spotlight Hinge 00"));
	SpotlightHingeMesh00->SetupAttachment(SpotlightMesh00);
	SpotlightHingeMesh01 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Spotlight Hinge 01"));
	SpotlightHingeMesh01->SetupAttachment(SpotlightMesh01);
	SpotlightHingeMesh02 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Spotlight Hinge 02"));
	SpotlightHingeMesh02->SetupAttachment(SpotlightMesh02);
	SpotlightHingeMesh03 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Spotlight Hinge 03"));
	SpotlightHingeMesh03->SetupAttachment(SpotlightMesh03);
	SpotlightHingeMesh04 = CreateDefaultSubobject<UStaticMeshComponent>(FName("Spotlight Hinge 04"));
	SpotlightHingeMesh04->SetupAttachment(SpotlightMesh04);

	SpotlightHingeMesh00->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpotlightHingeMesh01->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpotlightHingeMesh02->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpotlightHingeMesh03->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpotlightHingeMesh04->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

}

// Called when the game starts or when spawned
void AMetaShoot_OverheadLightBank::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMetaShoot_OverheadLightBank::UpdateAll()
{
	if (BMSAssetActive) {
		this->SetActorHiddenInGame(false);

		//Old Structure version compatibility
		if (needsUpdate)
		{

			if (VLightIntensity != 100)
			{
				Struct_LightBank.VLightIntensity = VLightIntensity;
			};

			if (VLightTemperature != 6500)
			{
				Struct_LightBank.VLightTemperature = VLightTemperature;
			};

			if (VLightTemperatureBool != true)
			{
				Struct_LightBank.VLightTemperatureBool = VLightTemperatureBool;
			};

			if (VLightTint != FLinearColor(1.0f, 1.0f, 1.0f))
			{
				Struct_LightBank.VLightTint = VLightTint;
			};

			if (VActorToTrack != nullptr && VActorToTrack->IsValidLowLevel())
			{
				Struct_LightBank.VActorToTrack = VActorToTrack;
			};

			needsUpdate = false;

		};

		AMetaShoot_OverheadLightBank::LookAtTarget();

		AMetaShoot_OverheadLightBank::UpdateLight();

		AMetaShoot_OverheadLightBank::UpdateLightMeshBP();

		AMetaShoot_OverheadLightBank::UpdateLightColor();

		AMetaShoot_OverheadLightBank::UpdateDiffuser();

		AMetaShoot_OverheadLightBank::UpdateHideMesh();
	}
	else {
		this->SetActorHiddenInGame(true);
	}
}

// Called every frame
void AMetaShoot_OverheadLightBank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AMetaShoot_OverheadLightBank::UpdateAll();
}

void AMetaShoot_OverheadLightBank::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	AMetaShoot_OverheadLightBank::UpdateAll();
}

void AMetaShoot_OverheadLightBank::LookAtTarget()
{
	if (IsValid(Struct_LightBank.VActorToTrack))
	{
		this->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Struct_LightBank.VActorToTrack->GetActorLocation()));
		this->AddActorLocalRotation(FRotator(0.0f, 90.0f, 90.0f));

		Struct_LightBank.VTargetName = Struct_LightBank.VActorToTrack->GetName();

		AMetaShoot_Target* TargetCast = Cast<AMetaShoot_Target>(Struct_LightBank.VActorToTrack);

		if (TargetCast)
		{
			Struct_LightBank.VTargetID = TargetCast->Struct_Target.VTargetID;
		}

	}
}

void AMetaShoot_OverheadLightBank::UpdateLight()
{
	LightScale = this->GetActorScale().X;

	RectLightComponent->SetVisibility(true);
	RectLightComponent->SetIntensity(Struct_LightBank.VLightIntensity);
	RectLightComponent->SetTemperature(Struct_LightBank.VLightTemperature);
	RectLightComponent->SetUseTemperature(Struct_LightBank.VLightTemperatureBool);
	RectLightComponent->SetLightColor(Struct_LightBank.VLightTint);
	RectLightComponent->SetIntensityUnits(ELightUnits::Candelas);

	
	RectLightComponent->SetBarnDoorAngle(45);
	RectLightComponent->SetBarnDoorLength(20);
	RectLightComponent->SetAttenuationRadius(1000);

	RectLightComponent->SetSourceWidth(210 * LightScale);
	RectLightComponent->SetSourceHeight(350 * LightScale);
	
}

void AMetaShoot_OverheadLightBank::UpdateLightColor()
{
	SB_RGBIntensity = RectLightComponent->Intensity / 25.5 / 10;

	//Kelvin Temperature to RGB | Credit to Tanner Helland for the base algorithm
	//Port to C++ for Unreal Engine by Jorge Valle Hurtado - byValle

	KtoRGB_Temperature = RectLightComponent->Temperature / 100;

	KtoRGB_Red = 0;
	KtoRGB_Green = 0;
	KtoRGB_Blue = 0;

	if (RectLightComponent->bUseTemperature == true)
	{
		//RED
		if (KtoRGB_Temperature <= 66)
		{
			KtoRGB_Red = 255;
		}

		else
		{
			KtoRGB_Red = 329.698727446 * pow(KtoRGB_Temperature - 60, -0.1332047592);
		}

		if (KtoRGB_Red < 0)
		{
			KtoRGB_Red = 0;
		}

		if (KtoRGB_Red > 255)
		{
			KtoRGB_Red = 255;
		}

		//GREEN
		if (KtoRGB_Temperature <= 66)
		{
			KtoRGB_Green = 99.4708025861 * log(KtoRGB_Temperature) - 161.1195681661;
		}

		else
		{
			KtoRGB_Green = 288.1221695283 * pow(KtoRGB_Temperature - 60, -0.0755148492);
		}

		if (KtoRGB_Green < 0)
		{
			KtoRGB_Green = 0;
		}
		if (KtoRGB_Green > 255)
		{
			KtoRGB_Green = 255;
		}

		//BLUE
		if (KtoRGB_Temperature >= 66)
		{
			KtoRGB_Blue = 255;
		}

		else
		{
			if (KtoRGB_Temperature <= 19)
			{
				KtoRGB_Blue = 0;
			}

			else
			{
				KtoRGB_Blue = 138.5177312231 * log(KtoRGB_Temperature - 10) - 305.0447927307;
			}
		}

		if (KtoRGB_Blue < 0)
		{
			KtoRGB_Blue = 0;
		}
		if (KtoRGB_Blue > 255)
		{
			KtoRGB_Blue = 255;
		}

		KtoRGB_Red = KtoRGB_Red / 10;
		KtoRGB_Green = KtoRGB_Green / 10;
		KtoRGB_Blue = KtoRGB_Blue / 10;
	}
	else
	{
		KtoRGB_Red = 25.5f;
		KtoRGB_Green = 25.5f;
		KtoRGB_Blue = 25.5f;
	}

	//FINAL RESULT AS FLINEARCOLOR
	KtoRGB = FLinearColor(KtoRGB_Red, KtoRGB_Green, KtoRGB_Blue, 1.0f);

	//Kelvin Temperature to RGB | Credit to Tanner Helland for the base algorithm
	//Port to C++ for Unreal Engine by Jorge Valle Hurtado - byValle
}

void AMetaShoot_OverheadLightBank::UpdateDiffuser()
{
	VLightMI = LightDiffuser->CreateDynamicMaterialInstance(0, 0, FName("DiffuserMaterial"));

	VLightMI->SetVectorParameterValue(FName("LightIntensity_Param"), FLinearColor(SB_RGBIntensity, SB_RGBIntensity, SB_RGBIntensity, 1.0));
	VLightMI->SetVectorParameterValue(FName("LightTemperatureRGB_Param"), KtoRGB);
	VLightMI->SetVectorParameterValue(FName("LightColor_Param"), Struct_LightBank.VLightTint);

	for (int32 i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:
			VSpotLightMI = SpotlightMesh00->CreateDynamicMaterialInstance(0, 0, FName("SpotLightMaterial"));
			break;

		case 1:
			VSpotLightMI = SpotlightMesh01->CreateDynamicMaterialInstance(0, 0, FName("SpotLightMaterial"));
			break;

		case 2:
			VSpotLightMI = SpotlightMesh02->CreateDynamicMaterialInstance(0, 0, FName("SpotLightMaterial"));
			break;

		case 3:
			VSpotLightMI = SpotlightMesh03->CreateDynamicMaterialInstance(0, 0, FName("SpotLightMaterial"));
			break;

		case 4:
			VSpotLightMI = SpotlightMesh04->CreateDynamicMaterialInstance(0, 0, FName("SpotLightMaterial"));
			break;
		}
		

		VSpotLightMI->SetVectorParameterValue(FName("LightIntensity_Param"), FLinearColor(SB_RGBIntensity * 10, SB_RGBIntensity * 10, SB_RGBIntensity * 10, 1.0));
		VSpotLightMI->SetVectorParameterValue(FName("LightTemperatureRGB_Param"), KtoRGB);
		VSpotLightMI->SetVectorParameterValue(FName("LightColor_Param"), Struct_LightBank.VLightTint);
	}
		
}

void AMetaShoot_OverheadLightBank::UpdateHideMesh()
{
	bool VHide = Struct_LightBank.VHideMesh;
	LightDiffuser->SetHiddenInGame(VHide, true);
	LightBox->SetHiddenInGame(VHide, true);
	LightBoxFrame->SetHiddenInGame(VHide, true);
	SpotlightMesh00->SetHiddenInGame(VHide, true);
	SpotlightMesh01->SetHiddenInGame(VHide, true);
	SpotlightMesh02->SetHiddenInGame(VHide, true);
	SpotlightMesh03->SetHiddenInGame(VHide, true);
	SpotlightMesh04->SetHiddenInGame(VHide, true);
	SpotlightHingeMesh00->SetHiddenInGame(VHide, true);
	SpotlightHingeMesh01->SetHiddenInGame(VHide, true);
	SpotlightHingeMesh02->SetHiddenInGame(VHide, true);
	SpotlightHingeMesh03->SetHiddenInGame(VHide, true);
	SpotlightHingeMesh04->SetHiddenInGame(VHide, true);

}