// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TravelogUI.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UILayerEnum.h"
#include "GameplayTagContainer.h"
#include "UIManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FWidgetInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Manager")
	FVector2D Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Manager")
	FVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Manager")
	ESlateVisibility Visibility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Manager")
	int32 ZOrder;
};



UCLASS(Blueprintable,BlueprintType)
class TRAVELOGTALES_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/*
	 *为UIManager添加观察者游戏事件发生时，自动更新UI元素，减少Tick不必要的性能损耗
	 */
	// 添加观察者
	UFUNCTION(BlueprintCallable, Category = "UI Events")
	void AddObserver(FGameplayTag EventTag, UTravelogUI* Observer);

	// 移除观察者
	UFUNCTION(BlueprintCallable, Category = "UI Events")
	void RemoveObserver(FGameplayTag EventTag, UTravelogUI* Observer);

	// 通知观察者
	UFUNCTION(BlueprintCallable, Category = "UI Events")
	void NotifyObservers(FGameplayTag EventTag);

	// 窗口管理
	UPROPERTY(BlueprintReadOnly, Category = "UI Manager")
	TMap<TSubclassOf<UTravelogUI>, FWidgetInfo> WindowManagement;

	UFUNCTION(BlueprintCallable, Category = "UI Manager")
	void SetWindowPosition(TSubclassOf<UTravelogUI> UIElement, FVector2D NewPosition);

	UFUNCTION(BlueprintCallable, Category = "UI Manager")
	void SetWindowSize(TSubclassOf<UTravelogUI> UIElement, FVector2D NewSize);

	UFUNCTION(BlueprintCallable, Category = "UI Manager")
	void SetWindowVisibility(TSubclassOf<UTravelogUI> UIElement, ESlateVisibility NewVisibility);

	UFUNCTION(BlueprintCallable, Category = "UI Manager")
	void SetWindowZOrder(TSubclassOf<UTravelogUI> UIElement, int32 NewZOrder);

	// 根据UI标签获取UI元素
	UFUNCTION(BlueprintCallable, Category = "UI Manager")
	TArray<TSubclassOf<UTravelogUI>> GetUIElementsByTag(FGameplayTag UITag);
	
	UFUNCTION(BlueprintCallable, Category = "UI Manager")
    TSubclassOf<UTravelogUI> GetCurrentUI() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI Manager")
	void CloseUI(TSubclassOf<UTravelogUI> UIElement,bool bDestroy = false);

	UFUNCTION(BlueprintCallable, Category = "UI Manager")
    void OpenUI(TSubclassOf<UTravelogUI> UIElement);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Layer")
	int32 UILayer;

private:

	UFUNCTION()
   void PushUI(TSubclassOf<UTravelogUI> UIElement);

	UFUNCTION()
	void PopUI();

	UFUNCTION()
	void ShowUI(TSubclassOf<UTravelogUI> UIElement);

	UFUNCTION()
	void HideUI(TSubclassOf<UTravelogUI> UIElement);
	
	TArray<TSubclassOf<UTravelogUI>> UIStackElement;

	//游戏初始UI(用于显示血条等游戏常驻UI)
	UPROPERTY()
	TArray<TSubclassOf<UTravelogUI>> DefaultInGameUI;

	UPROPERTY()
	TMap<TSubclassOf<UTravelogUI>, UTravelogUI*> UICache;

	TMap<FGameplayTag, TArray<UTravelogUI*>> ObserversMap;

	UTravelogUI* GetOrCreateUIElement(TSubclassOf<UTravelogUI> UIElement);
	
	
};
