// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadDataFromCSV.h"
#include <Runtime/Core/Public/Misc/Paths.h>
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
