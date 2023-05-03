// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Attribute/TravelogCooldownAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UTravelogCooldownAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 注册 RemainingCooldown 属性进行网络复制
	DOREPLIFETIME(UTravelogCooldownAttributeSet, RemainingCooldown);
}

void UTravelogCooldownAttributeSet::OnRep_RemainingCooldown(const FGameplayAttributeData& OldRemainingCooldown)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTravelogCooldownAttributeSet, RemainingCooldown, OldRemainingCooldown);
	OnCooldownChanged.Broadcast(RemainingCooldown.GetCurrentValue(), OldRemainingCooldown.GetCurrentValue());
}

void UTravelogCooldownAttributeSet::SetRemainingCooldown(float NewValue) 
{
	// 保证冷却时间不能为负数
	NewValue = FMath::Max(0.0f, NewValue);

	// 设置 RemainingCooldown 属性
	RemainingCooldown.SetCurrentValue(NewValue);
}

void UTravelogCooldownAttributeSet::ReduceRemainingCooldown(float DeltaTime)
{
	float NewValue = FMath::Max(0.0f, RemainingCooldown.GetCurrentValue() - DeltaTime);
	RemainingCooldown.SetCurrentValue(NewValue);
}

void UTravelogCooldownAttributeSet::InitRemainingCooldown(float InitialValue) const
{
	const_cast<UTravelogCooldownAttributeSet*>(this)->RemainingCooldown.SetCurrentValue(InitialValue);
}


void UTravelogCooldownAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetRemainingCooldownAttribute())
	{
		NewValue = FMath::Max(0.0f, NewValue);
	}
}
