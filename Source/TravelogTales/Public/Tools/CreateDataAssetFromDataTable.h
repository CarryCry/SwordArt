// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Items/TravelogItemBase.h"
#include "CreateDataAssetFromDataTable.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELOGTALES_API UCreateDataAssetFromDataTable : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting | GetDataTable")
	static TArray<UDataTable*> GetAllDataTablesInFile();
	
	UFUNCTION(BlueprintPure, Category = "Editor Scripting | GetUPrimaryClass")
	static  TArray<UTravelogItemBase*> GetPrimaryDataAssetSubclasses();

	UFUNCTION(BlueprintPure, Category = "Editor Scripting | GetStruct")
	static const UScriptStruct* GetDataTableStruct(UDataTable* DataTable);

	UFUNCTION(BlueprintPure, Category = "Editor Scripting | CheckDataTableDataClass")
	static  bool IsStructMemberOfClass(const UScriptStruct* Struct, const UClass* Class);
	
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting | GetDataTableRow")
	static  void CreateDataAssetFromDataTable(UDataTable* DataTable,const FString& PackagePath,const FString& AssetName,const FName DataTableRowName ,TSubclassOf<UTravelogItemBase> ItemClass);
	
};
