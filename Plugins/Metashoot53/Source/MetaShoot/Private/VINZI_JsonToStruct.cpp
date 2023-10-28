// Copyright 2023, VINZI All rights reserved


#include "VINZI_JsonToStruct.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "JsonObjectConverter.h"
#include "JsonUtilities.h"


VINZI_JsonToStruct::VINZI_JsonToStruct()
{
}

VINZI_JsonToStruct::~VINZI_JsonToStruct()
{
}


void VINZI_JsonToStruct::VINZIstruct_Transform(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, FTransform& OutTransform)
{
	TSharedPtr<FJsonObject> TransformObject = JsonObject->GetObjectField(FieldName);

	const TSharedPtr<FJsonObject>* rotationObject;
	const TSharedPtr<FJsonObject>* translationObject;
	const TSharedPtr<FJsonObject>* scale3DObject;

	if (TransformObject->TryGetObjectField("rotation", rotationObject))
	{
		float x, y, z, w;
		(*rotationObject)->TryGetNumberField("x", x);
		(*rotationObject)->TryGetNumberField("y", y);
		(*rotationObject)->TryGetNumberField("z", z);
		(*rotationObject)->TryGetNumberField("w", w);
		OutTransform.SetRotation(FQuat(x, y, z, w));
	}

	if (TransformObject->TryGetObjectField("translation", translationObject))
	{
		float x, y, z;
		(*translationObject)->TryGetNumberField("x", x);
		(*translationObject)->TryGetNumberField("y", y);
		(*translationObject)->TryGetNumberField("z", z);
		OutTransform.SetTranslation(FVector(x, y, z));
	}

	if (TransformObject->TryGetObjectField("scale3D", scale3DObject))
	{
		float x, y, z;
		(*scale3DObject)->TryGetNumberField("x", x);
		(*scale3DObject)->TryGetNumberField("y", y);
		(*scale3DObject)->TryGetNumberField("z", z);
		OutTransform.SetScale3D(FVector(x, y, z));
	}
}

void VINZI_JsonToStruct::VINZIstruct_LinearColor(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, FLinearColor& OutLinearColor)
{
	const TSharedPtr<FJsonObject>* ColorObject;

	if (JsonObject->TryGetObjectField(FieldName, ColorObject))
	{
		float r, g, b, a;

		(*ColorObject)->TryGetNumberField("r", r);
		(*ColorObject)->TryGetNumberField("g", g);
		(*ColorObject)->TryGetNumberField("b", b);
		(*ColorObject)->TryGetNumberField("a", a);

		OutLinearColor = FLinearColor(r, g, b, a);
	}
}

void VINZI_JsonToStruct::VINZIstruct_Bool(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, bool& OutBool)
{
	JsonObject->TryGetBoolField(FieldName, OutBool);
}

void VINZI_JsonToStruct::VINZIstruct_Float(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, float& OutFloat)
{
	JsonObject->TryGetNumberField(FieldName, OutFloat);
}

void VINZI_JsonToStruct::VINZIstruct_Int32(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, int32& OutInt32)
{
	JsonObject->TryGetNumberField(FieldName, OutInt32);
}

void VINZI_JsonToStruct::VINZIstruct_String(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, FString& OutString)
{
	JsonObject->TryGetStringField(FieldName, OutString);
}

/*
template <typename EnumType>
void VINZI_JsonToStruct::VINZIstruct_Enum(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, EnumType& OutEnum)
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
}*/