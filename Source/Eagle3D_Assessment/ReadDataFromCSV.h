// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
//#include "Misc/FileHelper.h"
#include <Runtime/Core/Public/Misc/FileHelper.h>
#include "ReadDataFromCSV.generated.h"


/**
 * 
 */
UCLASS()
class EAGLE3D_ASSESSMENT_API UReadDataFromCSV : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable, Category = "File IO")
		static FString LoadFileToString(FString FileDirectory);

	UFUNCTION(BlueprintCallable, Category = "File IO")
		static TArray<FString> LoadFileToStringArray(FString FileDirectory);
	
};
