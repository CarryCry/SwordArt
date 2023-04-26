// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/TravelogWeaponBase.h"
#include "Engine/AssetManager.h"
#include "Engine/DataTable.h"
#include "Items/TravelogItemBase.h"
#include "TravelogWeaponItem.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	LONGRANGE  UMETA(DisplayName="远程"),
	MELEE      UMETA(DisplayName="近战"),
};

UENUM(BlueprintType)
enum class EWeaponCategory_Melee : uint8
{
	ONEHANDSWORD  UMETA(DisplayName="单手剑"),
	TWOHANDSWORD  UMETA(DisplayName="斧头"),
	RAPIER        UMETA(DisplayName="细剑"),
	AXE           UMETA(DisplayName="斧头"),
};

UENUM(BlueprintType)
enum class EWeaponCategory_LongRange : uint8
{
	BOW  UMETA(DisplayName="弓"),
};

USTRUCT(BlueprintType)
struct FWeaponItem :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Information",meta=(DisplayName="武器名"))
	FText WeaponName;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Information",meta=(DisplayName="武器类型"))
	EWeaponType WeaponType;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Information",meta=(DisplayName="武器类别",EditCondition = "WeaponType == EWeaponType::MELEE",EditConditionHides))
	EWeaponCategory_Melee WeaponCategory_Melee;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Information",meta=(DisplayName="武器类别",EditCondition = "WeaponType == EWeaponType::LONGRANGE",EditConditionHides))
	EWeaponCategory_LongRange WeaponCategory_LongRange;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Information",meta=(DisplayName="武器"))
	TSubclassOf<ATravelogWeaponBase> WeaponActor;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Attribute",meta=(DisplayName="最大天命"))
	int32 MAXWeaponHealth;
	
	
};

UCLASS()
class TRAVELOGTALES_API UTravelogWeaponItem : public UTravelogItemBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FWeaponItem WeaponItem;
	
};
