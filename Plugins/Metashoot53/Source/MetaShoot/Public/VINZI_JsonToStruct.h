// Copyright 2023, VINZI All rights reserved

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */
class METASHOOT_API VINZI_JsonToStruct
{

public:
	VINZI_JsonToStruct();
	~VINZI_JsonToStruct();

	UFUNCTION()
		void VINZIstruct_Transform(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, FTransform& OutTransform);

	UFUNCTION()
		void VINZIstruct_LinearColor(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, FLinearColor& OutLinearColor);

	UFUNCTION()
		void VINZIstruct_Bool(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, bool& OutBool);

	UFUNCTION()
		void VINZIstruct_Float(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, float& OutFloat);

	UFUNCTION()
		void VINZIstruct_Int32(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, int32& OutInt32);

	UFUNCTION()
		void VINZIstruct_String(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, FString& OutString);

	/*template <typename EnumType>
	UFUNCTION()
		void VINZIstruct_Enum(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, EnumType& OutEnum);
	*/

	template <typename EnumType>
	void VINZIstruct_Enum(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, EnumType& OutEnum)
	{
		FString EnumValueString;
		if (JsonObject->TryGetStringField(FieldName, EnumValueString))
		{
			UEnum* Enum = StaticEnum<EnumType>();
			if (!Enum)
			{
				// Handle error - Enum not found
				return;
			}

			int32 EnumIndex = Enum->GetIndexByNameString(EnumValueString, EGetByNameFlags::None);
			if (EnumIndex == INDEX_NONE)
			{
				// Handle error - Enum value not found
				return;
			}

			OutEnum = static_cast<EnumType>(Enum->GetValueByIndex(EnumIndex));
		}
	}

};