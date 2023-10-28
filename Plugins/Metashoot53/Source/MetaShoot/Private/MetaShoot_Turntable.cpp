// Copyright 2023, VINZI Studio S.L. All rights reserved


#include "MetaShoot_Turntable.h"

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"

// Sets default values
AMetaShoot_Turntable::AMetaShoot_Turntable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Components

	Turntable_Root = CreateDefaultSubobject<USceneComponent>(FName("Turntable Root"));
	this->SetRootComponent(Turntable_Root);

	TurntableBase = CreateDefaultSubobject<UStaticMeshComponent>(FName("Base"));
	TurntableBase->SetupAttachment(Turntable_Root);
	TurntableBase->SetHiddenInGame(Struct_Turntable.VHideBase);
	TurntableBase->SetWorldScale3D(FVector(Struct_Turntable.VBaseScale, Struct_Turntable.VBaseScale, 1.0f));
	TurntableBase->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	TurntableBase->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	VActorComponent = CreateDefaultSubobject<UChildActorComponent>(FName("Actor"));
	VActorComponent->SetupAttachment(Turntable_Root);

	VMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	VMeshComponent->SetupAttachment(Turntable_Root);

	VArrowZ = CreateDefaultSubobject<UArrowComponent>(FName("Z Axis"));
	VArrowZ->SetupAttachment(Turntable_Root);
	VArrowZ->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	VArrowZ->SetWorldScale3D(FVector(10.0f, 0.12f, 0.12f));
	VArrowZ->SetArrowColor(FLinearColor(0.0f, 0.0f, 1.0f));
	VArrowZ->SetVisibility(Struct_Turntable.VPreviewZ);


	BStarted = false;

	BFinished = false;

	VFramerate = 30;

	Iframe = 0;

}

// Called when the game starts or when spawned
void AMetaShoot_Turntable::BeginPlay()
{
	Super::BeginPlay();

	/*auto richCurve = new FRichCurve();
	auto key = richCurve->AddKey(0.f, 0.f);
	richCurve->AddKey(0.5f, 1.f);
	richCurve->AddKey(1.5f, 0.f);
	richCurve->SetKeyTime(key, 10.0f);
	richCurve->SetKeyInterpMode(key, RCIM_Linear);

	auto curve = NewObject<UCurveFloat>();

	curve->FloatCurve = *richCurve;

	CurveTimeline.AddInterpFloat(curve, progressFunction, FName{ TEXT("EFFECT_TIMED") });*/

	
}

// Called every frame
void AMetaShoot_Turntable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!BStarted) {
		Iframe++;

		if (Iframe == 4) {
			BStarted = true;

			if (Struct_Turntable.VDelay == 0)
			{
				AMetaShoot_Turntable::StartRotation();
			}
			else
			{
				FTimerHandle UnusedHandle;
				GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMetaShoot_Turntable::StartRotation, Struct_Turntable.VDelay, false);
			}
		}
	}

	if (BStarted) {
		CurveTimeline.TickTimeline(DeltaTime);
	}
	

	/*float CurrentTime = GetWorld()->GetTimeSeconds();

	if (VRotate) {

		if (BStarted) {

			if (CurrentTime - StartTime > VRotationTime) {
				if (VLoop) {
					StartTime = CurrentTime;
				}
			}

			GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, FString::SanitizeFloat(GetActorRotation().Yaw));
			GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, FString::SanitizeFloat(StartRot));
			GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, FString::SanitizeFloat(VDegrees));

			float rotateValue;

			if (!BFinished) {

				if (VClockwise) {
					rotateValue = StartRot + (CurrentTime - StartTime) * (VDegrees / VRotationTime);
				}
				else {
					rotateValue = StartRot - (CurrentTime - StartTime) * (VDegrees / VRotationTime);
				}

				SetActorRotation(FRotator(0.0f, rotateValue, 0.0f));
			}

			if (!VLoop && CurrentTime - StartTime > VRotationTime) {

				BFinished = true;

				if (VClockwise) {
					rotateValue = StartRot + VDegrees;
				}
				else {
					rotateValue = StartRot - VDegrees;
				}

				SetActorRotation(FRotator(0.0f, rotateValue, 0.0f));
			}

		}

		if ((CurrentTime - VDelay) * VFramerate >= 1.0f && !BStarted) {
			BStarted = true;

			StartRot = GetActorRotation().Yaw;
			StartTime = CurrentTime;

			
		}
		else {
		}

	}*/

}

void AMetaShoot_Turntable::OnConstruction(const FTransform& Transform)
{
	BStarted = false;

	BFinished = false;

	Iframe = 0;

	/*if (VPreviousUVChecker != VUVChecker)
	{
		if (VUVChecker)
		{
			UpdateUVChecker();
		}
		else
		{
			VMaterial = NULL;
			VMeshComponent->SetMaterial(0, VMaterial);
			VMaterial = VMeshComponent->GetMaterial(0)->GetMaterial();
		}
	}

	VPreviousUVChecker = VUVChecker;*/

	
	
}


void AMetaShoot_Turntable::StartRotation()
{
	if (CurveFloat && Struct_Turntable.VRotate && VEnableRotation)
	{

		StartRot = GetActorRotation().Yaw;
		EndRot = GetActorRotation().Yaw;

		if (Struct_Turntable.VClockwise)
		{
			EndRot += Struct_Turntable.VDegrees;
		}
		else
		{
			EndRot -= Struct_Turntable.VDegrees;
		}

		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(true);
		

		CurveTimeline.PlayFromStart();
	}
}

void AMetaShoot_Turntable::TimelineProgress(float Value)
{
	float FValue = FMath::Lerp(StartRot, EndRot, Value * (100 / Struct_Turntable.VRotationTime));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, FString::SanitizeFloat(FValue));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, FString::SanitizeFloat(Value));
	
	SetActorRotation(FRotator(0.0f, FMath::Lerp(StartRot, EndRot, Value * (100 / Struct_Turntable.VRotationTime)), 0.0f));

	if (CurveTimeline.GetPlaybackPosition() >= Struct_Turntable.VRotationTime)
	{
		CurveTimeline.Stop();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, FString::SanitizeFloat(CurveTimeline.GetPlaybackPosition()));
		if (Struct_Turntable.VLoop)
		{
			CurveTimeline.PlayFromStart();
		}
	}
}


#if WITH_EDITOR
void AMetaShoot_Turntable::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_Turntable, VMesh)) {
		if (VMeshComponent)
		{
			VMeshComponent->SetStaticMesh(Struct_Turntable.VMesh);
			if (VMeshComponent->GetMaterial(0))
			{
				Struct_Turntable.VMaterial = VMeshComponent->GetMaterial(0)->GetMaterial();
			}
		}
		else
		{
			VMeshComponent->SetStaticMesh(NULL);
		}
	}

	/*if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_Turntable, VMaterial)) {
		if (VMeshComponent)
		{
			if (!VUVChecker)
			{
				VMeshComponent->SetMaterial(0, VMaterial);
			}
			if (!VMaterial)
			{
				if (VMeshComponent->GetMaterial(0))
				{
					VMaterial = VMeshComponent->GetMaterial(0)->GetMaterial();
				}
			}
		}
	}*/

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_Turntable, VTransformChild)) {
		if (VMeshComponent)
		{
			VMeshComponent->SetRelativeTransform(Struct_Turntable.VTransformChild);
		}
		if (VActorComponent)
		{
			VActorComponent->SetRelativeTransform(Struct_Turntable.VTransformChild);
		}
	}

	//if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_Turntable, VUVChecker)) {
	//	//AMetaShoot_Turntable::UpdateUVChecker();
	//}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_Turntable, VHideBase)) {
		TurntableBase->SetHiddenInGame(Struct_Turntable.VHideBase);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_Turntable, VPreviewZ)) {
		VArrowZ->SetVisibility(Struct_Turntable.VPreviewZ);
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_Turntable, VBaseScale)) {
		TurntableBase->SetWorldScale3D(FVector(Struct_Turntable.VBaseScale, Struct_Turntable.VBaseScale, 1.0f));
	}

	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_Turntable, VActor)) {
		/*if (VActorPrevious)
		{
			//VActorPrevious->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		}*/
		if (IsValid(Struct_Turntable.VActor))
		{
			Struct_Turntable.VActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
			VActorPrevious = Struct_Turntable.VActor;
			//VActorComponent->SetChildActorClass(Struct_Turntable.VActor->GetClass());
		}
		else
		{
			//VActorComponent->SetChildActorClass(NULL);
		}
	}

	/*if (PropertyName == GET_MEMBER_NAME_CHECKED(AMetaShoot_Turntable, VActor2)) {
		if (VActor2)
		{
			VActorComponent->SetChildActorClass(VActor2);
		}
		else
		{
			VActorComponent->SetChildActorClass(NULL);
		}
	}*/
}
#endif