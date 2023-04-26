// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"

void UUIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

void UUIManager::AddObserver(FGameplayTag EventTag, UTravelogUI* Observer)
{
	if (!ObserversMap.Contains(EventTag))
	{
		ObserversMap.Add(EventTag, TArray<UTravelogUI*>());
	}

	ObserversMap[EventTag].Add(Observer);
}

void UUIManager::RemoveObserver(FGameplayTag EventTag, UTravelogUI* Observer)
{
	if (ObserversMap.Contains(EventTag))
	{
		ObserversMap[EventTag].Remove(Observer);
	}
}

void UUIManager::NotifyObservers(FGameplayTag EventTag)
{
	if (ObserversMap.Contains(EventTag))
	{
		for (UTravelogUI* Observer : ObserversMap[EventTag])
		{
			Observer->OnGameEvent(EventTag);
		}
	}
}

void UUIManager::SetWindowPosition(TSubclassOf<UTravelogUI> UIElement, FVector2D NewPosition)
{
	if (UTravelogUI** WidgetInstancePtr = UICache.Find(UIElement))
	{
		UTravelogUI* WidgetInstance = *WidgetInstancePtr;
		WidgetInstance->SetPositionInViewport(NewPosition);
	}
}

void UUIManager::SetWindowSize(TSubclassOf<UTravelogUI> UIElement, FVector2D NewSize)
{
	if (UTravelogUI** WidgetInstancePtr = UICache.Find(UIElement))
	{
		UTravelogUI* WidgetInstance = *WidgetInstancePtr;
		WidgetInstance->SetDesiredSizeInViewport(NewSize);
	}
}

void UUIManager::SetWindowVisibility(TSubclassOf<UTravelogUI> UIElement, ESlateVisibility NewVisibility)
{
	if (UTravelogUI** WidgetInstancePtr = UICache.Find(UIElement))
	{
		UTravelogUI* WidgetInstance = *WidgetInstancePtr;
		WidgetInstance->SetVisibility(NewVisibility);
	}
}

void UUIManager::SetWindowZOrder(TSubclassOf<UTravelogUI> UIElement, int32 NewZOrder)
{
	if (UTravelogUI** WidgetInstancePtr = UICache.Find(UIElement))
	{
		UTravelogUI* WidgetInstance = *WidgetInstancePtr;
		WidgetInstance->RemoveFromParent();
		WidgetInstance->AddToViewport(NewZOrder);
	}
}


TArray<TSubclassOf<UTravelogUI>> UUIManager::GetUIElementsByTag(FGameplayTag UITag)
{
	TArray<TSubclassOf<UTravelogUI>> UIElementsWithTag;

	for (const TSubclassOf<UTravelogUI>& UIElement : UIStackElement)
	{
		if (UIElement->GetDefaultObject<UTravelogUI>()->UITag == UITag)
		{
			UIElementsWithTag.Add(UIElement);
		}
	}

	return UIElementsWithTag;
}


TSubclassOf<UTravelogUI> UUIManager::GetCurrentUI() const
{
	if (UIStackElement.Num() > 0)
	{
		return UIStackElement.Last();
	}

	return nullptr;
}

void UUIManager::CloseUI(TSubclassOf<UTravelogUI> UIElement,bool bDestroy)
{
	TArray<TSubclassOf<UTravelogUI>> UIElementsToClose;
	UIElementsToClose.Push(UIElement);

	while (UIElementsToClose.Num() > 0)
	{
		TSubclassOf<UTravelogUI> CurrentUIElement = UIElementsToClose.Pop();

		// 隐藏UI
		HideUI(CurrentUIElement);

		// 从UIStackElement中移除UI
		UIStackElement.RemoveSingleSwap(CurrentUIElement, false);

		// 将子类UI添加到UIElementsToClose中以便后续处理
		TArray<TSubclassOf<UTravelogUI>> ChildUIElements = GetUIElementsByTag(CurrentUIElement->GetDefaultObject<UTravelogUI>()->UITag);
		UIElementsToClose.Append(ChildUIElements);

		// 如果bDestroy为真，则从UICache中移除UI并销毁它
		if (bDestroy)
		{
			if (UTravelogUI** WidgetInstancePtr = UICache.Find(CurrentUIElement))
			{
				UTravelogUI* WidgetInstance = *WidgetInstancePtr;
				WidgetInstance->RemoveFromParent(); // 确保从父容器中移除
				UICache.Remove(CurrentUIElement);
				WidgetInstance->ConditionalBeginDestroy();
			}
		}
	}
}

void UUIManager::OpenUI(TSubclassOf<UTravelogUI> UIElement)
{
	// 首先检查指定的UI元素是否已经在UIStackElement中
	bool bIsUIAlreadyOpened = false;
	for (TSubclassOf<UTravelogUI> CurrentUI : UIStackElement)
	{
		if (CurrentUI == UIElement)
		{
			bIsUIAlreadyOpened = true;
			break;
		}
	}

	// 如果UI元素尚未打开，则将其推送到UIStackElement并显示
	if (!bIsUIAlreadyOpened)
	{
		PushUI(UIElement);
	}
	else
	{
		// 如果UI元素已经打开，则显示一个警告
		UE_LOG(LogTemp, Warning, TEXT("Attempting to open an already opened UI element!"));
	}
}

void UUIManager::PushUI(TSubclassOf<UTravelogUI> UIElement)
{
	if (UIElement->GetDefaultObject<UTravelogUI>()->UITag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("UI.InGameUI"), false)))
	{
		DefaultInGameUI.Add(UIElement);
	}
	else
	{
		UIStackElement.Push(UIElement);
	
	}
	ShowUI(UIElement);
}

void UUIManager::PopUI()
{
	if (UIStackElement.Num() > 0)
	{
		TSubclassOf<UTravelogUI> UIElement = UIStackElement.Last();

		if (!DefaultInGameUI.Contains(UIElement))
		{
			HideUI(UIElement);
			UIStackElement.Pop();
		}
	}
}

void UUIManager::ShowUI(TSubclassOf<UTravelogUI> UIElement)
{
	UTravelogUI* WidgetInstance = GetOrCreateUIElement(UIElement);

	if (WidgetInstance)
	{
		// 根据UI元素的层级分配ZOrder值
		int32 ZOrder = static_cast<int32>(WidgetInstance->UILayer);
		WidgetInstance->AddToViewport(ZOrder);
	}
}

void UUIManager::HideUI(TSubclassOf<UTravelogUI> UIElement)
{
	UTravelogUI* WidgetInstance = nullptr;

	if (UTravelogUI** WidgetInstancePtr = UICache.Find(UIElement))
	{
		WidgetInstance = *WidgetInstancePtr;
		WidgetInstance->RemoveFromViewport();
	}
}

UTravelogUI* UUIManager::GetOrCreateUIElement(TSubclassOf<UTravelogUI> UIElement)
{
	UTravelogUI* WidgetInstance = nullptr;

	if (UICache.Contains(UIElement))
	{
		WidgetInstance = UICache[UIElement];
	}
	else
	{
		WidgetInstance = CreateWidget<UTravelogUI>(GetWorld(), UIElement);
		UICache.Add(UIElement, WidgetInstance);
	}

	return WidgetInstance;
}


