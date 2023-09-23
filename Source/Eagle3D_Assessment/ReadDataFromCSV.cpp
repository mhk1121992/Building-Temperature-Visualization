// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadDataFromCSV.h"
#include <Runtime/Core/Public/Misc/Paths.h>
//#include "Json.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include <Runtime/Core/Public/HAL/PlatformFilemanager.h>


FString UReadDataFromCSV::LoadFileToString(FString FileDirectory)
{
	FString Result;
	IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();

	if (File.CreateDirectory(*FileDirectory))
	{
		FString MyFile = FileDirectory;
		FFileHelper::LoadFileToString(Result, *MyFile);
	}

	return Result;
}

TArray<FString> UReadDataFromCSV::LoadFileToStringArray(FString FileDirectory)
{
	TArray<FString> Result;
	IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();

	if (File.CreateDirectory(*FileDirectory))
	{
		FString MyFile = FileDirectory;
		FFileHelper::LoadFileToStringArray(Result, *MyFile);
	}

	return Result;
}



// ------------------------------- //

FJsonToStruct UReadDataFromCSV::ReadStructFromJson(FString JsonString, bool& bOutSuccess, FString& OutInfoMessage)
{
	TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonString, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return FJsonToStruct();
	}

	FJsonToStruct RetStruct;

	// try to convert generic json object to the desired struct. Output goes in RetStruct
	if (!FJsonObjectConverter::JsonObjectToUStruct<FJsonToStruct>(JsonObject.ToSharedRef(), &RetStruct))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Reading Json Failed - Was not able to deserialize the json string. Is it the right format? - '%s'"), *JsonString);
		return FJsonToStruct();
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Reading Json Succeede..."));
	return RetStruct;
}

TSharedPtr<FJsonObject> UReadDataFromCSV::ReadJson(FString JsonString, bool& bOutSuccess, FString& OutInfoMessage)
{
	//FString JsonString;
	
	if (!bOutSuccess)
	{
		return nullptr;
	}

	TSharedPtr<FJsonObject> RetJsonObject;

	// try to convert string to json object. Output goes in RetJsonObject
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Reading Json Failed - Was not able to deserialize the json string. Is it the right format? - '%s'"), *JsonString);
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Reading Json Succeeded..."));
	return RetJsonObject;
}





