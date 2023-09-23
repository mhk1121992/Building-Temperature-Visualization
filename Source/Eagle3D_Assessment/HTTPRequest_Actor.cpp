// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPRequest_Actor.h"
#include "Json.h"
#include "HttpModule.h"
#include "JsonUtilities.h"
//#include "Runtime/Online/HTTP/Public/Http.h"
//#include "Serialization/JsonSerializer.h"

// Sets default values
AHTTPRequest_Actor::AHTTPRequest_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

// Called when the game starts or when spawned
void AHTTPRequest_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHTTPRequest_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHTTPRequest_Actor::GetJsonResponse(FString API_Endpoint, FString& OutJsonString)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();


	Request->OnProcessRequestComplete().BindUObject(this, &AHTTPRequest_Actor::OnResponseReceived);
	

	if (!API_Endpoint.IsEmpty())
	{
		Request->SetURL(API_Endpoint);
		Request->SetVerb("GET");
		Request->ProcessRequest();
		UE_LOG(LogTemp, Error, TEXT("Code is working.."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EMPTY URL"));
	}
	OutJsonString = *JsonResponse;
	UE_LOG(LogTemp, Display, TEXT("OutJsonString %s"), *OutJsonString);

}

void AHTTPRequest_Actor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceed)
{
	/*UE_LOG(LogTemp, Display, TEXT("Response %s"), *Response->GetContentAsString());
	UE_LOG(LogTemp, Display, TEXT("Response Content Type %s"), *Response->GetContentType());*/

	JsonResponse = Response->GetContentAsString();
	//UE_LOG(LogTemp, Display, TEXT("Response %s"), *JsonResponse);
	/*TSharedPtr<FJsonObject> ResponseObj = MakeShared<FJsonObject>();
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);*/
}


//............................................................................................

//FString AHTTPRequest_Actor::GetJsonFromApiEndpoint(const FString& EndpointUrl)
//{
//    
//    // Create an HTTP request.
//    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
//    HttpRequest->SetURL(EndpointUrl);
//    HttpRequest->SetVerb(TEXT("GET"));
//
//    FString JsonContent;
//    TArray<FString> MyArray;
//    // Set up the response callback.
//    HttpRequest->OnProcessRequestComplete().BindLambda([&](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
//        {
//            
//            // Check if the request was successful.
//            if (bSucceeded && Response.IsValid() && Response->GetResponseCode() == EHttpResponseCodes::Ok)
//            {
//                // Get the JSON content as a string.
//                
//                JsonContent = Response->GetContentAsString();
//                UE_LOG(LogTemp, Log, TEXT("Received HTTP response code: %d"), Response->GetResponseCode());
//                UE_LOG(LogTemp, Log, TEXT("Received JSON content: %s"), *JsonContent);
//
//                // Implement safety checks or validation logic here.
//                // For example, check if the JSON content meets your criteria.
//
//                if (IsValidJson(JsonContent) && HasExpectedFields(JsonContent))
//                {
//                    // Handle the JSON data here.
//                    UE_LOG(LogTemp, Log, TEXT("Received JSON response: %s"), *JsonContent);
//                }
//                else
//                {
//                    // Log a warning or handle invalid JSON here.
//                    UE_LOG(LogTemp, Warning, TEXT("Received JSON content does not meet safety criteria."));
//                }
//            }
//            else
//            {
//                // Log an error if the request failed.
//                UE_LOG(LogTemp, Error, TEXT("HTTP request failed or received an invalid response."));
//            }
//        });
//
//    // Send the request and wait for the response.
//    HttpRequest->ProcessRequest();
//    return JsonContent;
//}
//
//
//bool AHTTPRequest_Actor::IsValidJson(const FString& JsonString)
//{
//    // Implement JSON validation logic here.
//    // Return true if the JSON is valid; otherwise, return false.
//    // You can use Unreal's JSON parsing functions for validation.
//    // For simplicity, we assume any non-empty string is valid JSON.
//    return !JsonString.IsEmpty();
//}
//
//bool AHTTPRequest_Actor::HasExpectedFields(const FString& JsonString)
//{
//    // Implement checks for expected fields in the JSON.
//    // Modify this function according to your requirements.
//    // As an example, let's assume you expect a "data" field in the JSON.
//
//    if (JsonString.Contains(TEXT("\"temperature\":")))
//    {
//        return true;
//    }
//
//    return false;
//}





