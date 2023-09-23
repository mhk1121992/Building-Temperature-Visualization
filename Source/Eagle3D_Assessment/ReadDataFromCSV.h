// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
//#include "Misc/FileHelper.h"
#include <Runtime/Core/Public/Misc/FileHelper.h>
#include "Http.h"
#include "ReadDataFromCSV.generated.h"

class FJsonObject;
/**
 * 
 */

USTRUCT(BlueprintType, Category = "File IO")
struct FJsonToStruct
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "File IO")
		FString ID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "File IO")
		FString Temperature;
};


UCLASS()
class EAGLE3D_ASSESSMENT_API UReadDataFromCSV : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "File IO")
		static FString LoadFileToString(FString FileDirectory);

	UFUNCTION(BlueprintCallable, Category = "File IO")
		static TArray<FString> LoadFileToStringArray(FString FileDirectory);



	// ------------------------------- //
	
	UFUNCTION(BlueprintCallable, Category = "File IO")
		static FJsonToStruct ReadStructFromJson(FString JsonString, bool& bOutSuccess, FString& OutInfoMessage);

	// can't be called from Blueprint because it's using FJsonObject which is not available in Blueprint
	static TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);
	
	
};
