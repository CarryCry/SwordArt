// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/CreateDataAssetFromDataTable.h"
#include "ContentBrowserDataSource.h"
#include "JsonObjectConverter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/ObjectLibrary.h"


TArray<UDataTable*> UCreateDataAssetFromDataTable::GetAllDataTablesInFile()
{
	TArray<UDataTable*> DataTables;

	// 创建一个 Object Library
	UObjectLibrary* ObjectLibrary = NewObject<UObjectLibrary>(UObjectLibrary::StaticClass());

	// 加载文件内所有的 UObject
	ObjectLibrary->LoadAssetDataFromPath("/Game/DataTables");

	// 遍历所有的 UObject，找出所有的 DataTable
	TArray<FAssetData> AssetDataList;
	ObjectLibrary->GetAssetDataList(AssetDataList);

	for (const FAssetData& AssetData : AssetDataList)
	{
		if (AssetData.GetClass() == UDataTable::StaticClass())
		{
			UDataTable* DataTable = Cast<UDataTable>(AssetData.GetAsset());
			if (DataTable)
			{
				DataTables.Add(DataTable);
			}
		}
	}

	return DataTables;
}

TArray<UTravelogItemBase*> UCreateDataAssetFromDataTable::GetPrimaryDataAssetSubclasses()
{
	// 获取所有类
	TArray<FAssetData> AssetData;
	const UClass* BaseClass = UTravelogItemBase::StaticClass();
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByClass(BaseClass->GetFName(), AssetData);

	// 过滤出所有子类
	TArray<UTravelogItemBase*> Subclasses;

	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* AssetClass = *It;
		if (AssetClass && AssetClass->IsChildOf(BaseClass) && !AssetClass->HasAnyClassFlags(CLASS_Abstract | CLASS_Deprecated))
		{
			UTravelogItemBase* Item = Cast<UTravelogItemBase>(AssetClass->GetDefaultObject());
			if (Item != nullptr)
			{
				Subclasses.Add(Item);
			}
		}
	}

	return Subclasses;
}

const UScriptStruct* UCreateDataAssetFromDataTable::GetDataTableStruct(UDataTable* DataTable)
{
	const UScriptStruct* Struct = DataTable->GetRowStruct();
	return Struct;
}

bool UCreateDataAssetFromDataTable::IsStructMemberOfClass(const UScriptStruct* Struct, const UClass* Class)
{
	// 遍历 Class 的所有属性，查找是否存在与 Struct 相同的结构体类型
	for (TFieldIterator<const FProperty> PropertyIt(Class, EFieldIteratorFlags::IncludeSuper); PropertyIt; ++PropertyIt)
	{
		const FStructProperty* StructProperty = CastField<const FStructProperty>(*PropertyIt);
		if (StructProperty && StructProperty->Struct == Struct)
		{
			// 找到相同的结构体类型，说明 Struct 是 Class 的成员变量
			return true;
		}
	}

	// 没有找到相同的结构体类型，说明 Struct 不是 Class 的成员变量
	return false;
}

void UCreateDataAssetFromDataTable::CreateDataAssetFromDataTable(UDataTable* DataTable, const FString& PackagePath,
	const FString& AssetName, const FName DataTableRowName, TSubclassOf<UTravelogItemBase> ItemClass)
{
	// 检查输入是否有效
	if (!DataTable || !ItemClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("无效输入！")); // 输出警告信息
		return;
	}

	// 创建一个新的 Package
	UPackage* NewPackage = CreatePackage(*PackagePath);

	// 用 ItemClass 创建一个新的 USwordItemBase 对象
	UTravelogItemBase* ThisItem = NewObject<UTravelogItemBase>(NewPackage, ItemClass.Get(), *AssetName, EObjectFlags::RF_Public | RF_Standalone);

	if (ThisItem)
	{
		// 遍历 ItemClass 中的所有属性
		for(TFieldIterator<FProperty> It(ItemClass);It;++It)
		{
			// 判断当前属性是否为结构体类型，并且结构体类型与 DataTable 中行的结构相同
			if(FStructProperty* ItemProperty = CastField<FStructProperty>(*It))
			{
				if(ItemProperty->Struct == DataTable->GetRowStruct())
				{
					// 获取 DataTable 中指定行的数据
					void* ItemRowDataPtr = DataTable->GetRowMap().FindRef(DataTableRowName);
					FString CopyValue;
					// 将指定行的数据转换为文本格式
					ItemProperty->Struct->ExportText(CopyValue,ItemRowDataPtr,ItemRowDataPtr,DataTable,PPF_Copy,nullptr);

					// 将转换后的文本格式数据赋值给对应的属性
					ItemProperty->ImportText(*CopyValue, ItemProperty->ContainerPtrToValuePtr<void>(ThisItem), PPF_None, nullptr);
				}
			}
            
		}

		// 在 Asset Registry 中注册新的 Asset
		FAssetRegistryModule::AssetCreated(ThisItem);
		// 标记当前 Package 为 Dirty，方便在资源浏览器中保存变更
		ThisItem->GetOutermost()->MarkPackageDirty();
	}
}
