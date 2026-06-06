// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
struct FOnAttributeChangeData;

USTRUCT(BlueprintType)
struct FUIWidgetRow: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag MessageTag=FGameplayTag();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UAuraUserWidget> MessageWidgetClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message=FText();
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image=nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowDelegate, const FUIWidgetRow&, Row);

UCLASS(BlueprintType, Blueprintable)
class MYAURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallBacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnMaxManaChangedSignature OnMaxManaChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FMessageWidgetRowDelegate MessageWidgetRowDelegate;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);
	void EffectAssetTags(const FGameplayTagContainer& Container);
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
