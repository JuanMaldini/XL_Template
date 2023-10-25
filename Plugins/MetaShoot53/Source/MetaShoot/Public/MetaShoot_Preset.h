// Copyright 2023, VINZI Studio S.L. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "MetaShoot_Manifest.h"
#include "GameFramework/Actor.h"
#include "MetaShoot_Preset.generated.h"

UCLASS()
class METASHOOT_API AMetaShoot_Preset : public AActor
{
    GENERATED_BODY()

public:
    AMetaShoot_Preset();

    UPROPERTY(BlueprintReadWrite, Category = "Preset")
        FSMetaShoot_Studio Struct_Studio;
};