﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ClingSetting.h"

#include "JsonObjectConverter.h"
#include "UCling.h"
#include "Interfaces/IPluginManager.h"

UClingSetting::UClingSetting()
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("Cling");
}

FName UClingSetting::GetCategoryName() const
{
	return Super::GetCategoryName();
}

FName UClingSetting::GetContainerName() const
{
	return Super::GetContainerName();
}

FName UClingSetting::GetSectionName() const
{
	return Super::GetSectionName();
}

void UClingSetting::RefreshIncludePaths()
{
	// auto& Module = FModuleManager::Get().GetModuleChecked<FUClingModule>(TEXT("UCling"));
    FString ModuleBuildInfoJson = IPluginManager::Get().FindPlugin("UCling")->GetBaseDir()/TEXT("ModuleBuildInfos.json");
    FString JsonString;
    FFileHelper::LoadFileToString(JsonString,*ModuleBuildInfoJson);

    // Parse the JSON string
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
    TSharedPtr<FJsonObject> JsonObject;    

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
        // Access the "Modules" object
        TSharedPtr<FJsonObject> ModulesObject = JsonObject->GetObjectField(TEXT("Modules"));
        if (ModulesObject && ModulesObject.IsValid())
        {
            // Access the "UnrealClingTestPack" object within "Modules"
            for (auto Value : ModulesObject->Values)
            {
                auto& Struct = ModuleBuildInfos.Add(FName(Value.Key));
                FJsonObjectConverter::JsonObjectToUStruct(Value.Value->AsObject().ToSharedRef(),&Struct);
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to find 'Modules' object in JSON!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON!"));
    }
}
