// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ActionRPGGame.h"
#include "Types/ARStructTypes.h"
#include "GameplayTagsModule.h"
#include "AREdEngine.h"

UAREdEngine::UAREdEngine(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void UAREdEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);
	FString table = "DataTable'/Game/Blueprints/Data/ChestItemData.ChestItemData'";
	ChestItemDataTable = LoadObject<UDataTable>(NULL, *table, NULL, LOAD_None, NULL);

	FString Weapons = "DataTable'/Game/Blueprints/Data/WeaponItemData.WeaponItemData'";
	WeaponItemDataTable = LoadObject<UDataTable>(NULL, *Weapons, NULL, LOAD_None, NULL);
	//DataTable'/Game/Blueprints/Data/GameTags.GameTags'
	IGameplayTagsModule& GameplayTagsModule = IGameplayTagsModule::Get();
	FString Tags = "DataTable'/Game/Blueprints/Data/GameTags.GameTags'";

	//UDataTable* justDeleteMe = LoadObject<UDataTable>(NULL, *Tags, NULL, LOAD_None, NULL);

	TArray<FString> TagsList;
	TagsList.Add(Tags);
	GameplayTagsModule.GetGameplayTagsManager().LoadGameplayTagTables(TagsList);
}
