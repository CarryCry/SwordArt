// Fill out your copyright notice in the Description page of Project Settings.


#include "UITest/UIManagerComponent.h"
#include "Kismet/GameplayStatics.h"

void UUIManagerComponent::InitUIStates_Implementation()
{
	auto PC = UGameplayStatics::GetPlayerController(GetOwner(),0);

	if(!PC->IsLocalController())
	{
		return;
	}

	for(TTuple<FName,TSubclassOf<UUIState>>UI : UIStates)
	{
		auto Widget = CreateWidget<UUIState>(PC,UI.Value.Get(),UI.Key);

		UIInstances.Add(UI.Key,Widget);
	}
	
}



UUIState* UUIManagerComponent::GetUI_Implementation(FName UIName)
{
	UUIState** UI = UIInstances.Find(UIName);

	if(UI != nullptr)
	{
		return *UI;
	}

	return nullptr;
}

void UUIManagerComponent::PushUIState(FName UIName)
{
	auto UI = GetUI(UIName);
	if(UI==nullptr)
	{
		return;
	}
	TScriptInterface<IStackStateInterface> Interface(UI);

	PushState(UI);
	
}

void UUIManagerComponent::GetCurrentUIState(TSubclassOf<UUIState> StateClass, TEnumAsByte<EUIStateCasResult>& IsValid,
	UUIState*& OutState)
{
	if(StateCount()<=0)
	{
		IsValid = Failed;
		return;
	}

	UUIState* State = Cast<UUIState>(GetCurrentState().GetObjectRef());

	IsValid = State !=nullptr && State->GetClass()->IsChildOf(StateClass) ? Success : Failed;

	if (IsValid == Success)
	{
		OutState =State;
	}
}

void UUIManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	InitUIStates();
}

void UUIManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
