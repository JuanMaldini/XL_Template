// Copyright 2023, VINZI Studio S.L. All rights reserved


#include "MetaShoot_DSLRCamera.h"

#include "Components/StaticMeshComponent.h"

//CameraMesh02 = CreateDefaultSubobject<UStaticMeshComponent>(FName("CameraMesh02"));

void AMetaShoot_DSLRCamera::OnConstruction(const FTransform& Transform)
{
	if (BMSAssetActive) {

		if (needsUpdate)
		{

			if (VCameraMeshHidden != false)
			{
				DSLR.VCameraMeshHidden = VCameraMeshHidden;
			};

			if (VCameraMeshScale != 2.5)
			{
				DSLR.VCameraMeshScale = VCameraMeshScale;
			};

			if (VActorToTrack != nullptr && VActorToTrack->IsValidLowLevel())
			{
				DSLR.VActorToTrack = VActorToTrack;
			};

			needsUpdate = false;

		};

		UpdateDSLR();

		AMetaShoot_DSLRCamera::DefineFocusTarget();
		
	}
}

void AMetaShoot_DSLRCamera::DefineFocusTarget()
{
	if (IsValid(DSLR.VActorToTrack))
	{
		DSLR.VTargetName = DSLR.VActorToTrack->GetName();
	}

	AMetaShoot_Target* TargetCast = Cast<AMetaShoot_Target>(DSLR.VActorToTrack);

	if (TargetCast)
	{
		DSLR.VTargetID = TargetCast->Struct_Target.VTargetID;
	}
}



//void AMetaShoot_DSLRCamera::FixDepthOfField()
//{
//	/*FString VCommand = "r.TemporalAA.Upsampling 0";
//	GetWorld()->Exec(GetWorld(), *VCommand);*/
//
//	AMetaShoot_DSLRCamera::FixDOFBP();
//
//	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, "DOF Fixed - r.TemporalAA.Upsampling 0. Credit to William Faucher");
//	
//}

//#if WITH_EDITOR
//void AMetaShoot_DSLRCamera::PostEditChangeProperty(struct FPropertyChangedEvent& e)
//{
//	Super::PostEditChangeProperty(e);
//
//	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
//
//	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_DSLRCamera, VCameraMeshHidden)) {
//		CameraMeshHide();
//	}
//
//}
//#endif