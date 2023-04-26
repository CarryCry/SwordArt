// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TravelogEquipmentComponent.h"

#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UTravelogEquipmentComponent::UTravelogEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UTravelogEquipmentComponent::EquipWeapon(EEquipmentSlot WeaponSlot, UTravelogWeaponItem* WeaponItem)
{
	if (!WeaponItem)
	{
		return false;
	}

	// 如果在给定插槽中已经有武器，则先卸下
	if (EquippedWeapons.Contains(WeaponSlot))
	{
		UnequipWeapon(WeaponSlot);
	}

	// 将枚举值转换为插槽名称
	FName SocketName = FName(*UEnum::GetValueAsString(WeaponSlot));

	// 实例化武器并将其附加到指定的插槽上
	ATravelogWeaponBase* SpawnedWeapon = GetWorld()->SpawnActor<ATravelogWeaponBase>(WeaponItem->WeaponItem.WeaponActor);
	USkeletalMeshComponent* MeshComponent = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	SpawnedWeapon->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);

	// 更新 EquippedWeapons 映射
	EquippedWeapons.Add(WeaponSlot, WeaponItem);
	EquippedWeaponActors.Add(WeaponSlot, SpawnedWeapon);

	OnWeaponEquipped.Broadcast(WeaponSlot, WeaponItem);


	return true;
}

bool UTravelogEquipmentComponent::UnequipWeapon(EEquipmentSlot WeaponSlot)
{
	if (!EquippedWeapons.Contains(WeaponSlot))
	{
		return false;
	}

	// 从插槽上卸下武器并销毁
	AActor* UnequippedWeapon = EquippedWeaponActors[WeaponSlot];
	UnequippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	UnequippedWeapon->Destroy();

	// 从 EquippedWeapons 映射中移除武器
	EquippedWeapons.Remove(WeaponSlot);
	EquippedWeaponActors.Remove(WeaponSlot);

	OnWeaponUnequipped.Broadcast(WeaponSlot);
	
	return true;
}




