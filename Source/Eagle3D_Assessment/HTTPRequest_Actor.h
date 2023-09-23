// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "HTTPRequest_Actor.generated.h"

UCLASS()
class EAGLE3D_ASSESSMENT_API AHTTPRequest_Actor : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AHTTPRequest_Actor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HTTP Request");
	FString URL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HTTP Request");
	FString JsonResponse;

	UPROPERTY()
		USceneComponent* Root;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void GetJsonResponse(FString API_Endpoint, FString &OutJsonString);

	/*UFUNCTION(BlueprintCallable)
		FString GetJsonFromApiEndpoint(const FString& EndpointUrl);*/


private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceed);
	/*bool IsValidJson(const FString& JsonString);
	bool HasExpectedFields(const FString& JsonString);*/
};
