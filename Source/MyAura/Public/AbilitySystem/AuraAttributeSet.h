// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties(){}
	
	FGameplayEffectContextHandle ContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC=nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor=nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter=nullptr;
	UPROPERTY()
	AController* SourceController=nullptr;
	
	UPROPERTY()
	UAbilitySystemComponent* TargetASC=nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor=nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter=nullptr;
	UPROPERTY()
	AController* TargetController=nullptr;
};

template<class T>
using TAttributeFuncPtr = TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class MYAURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	public:
	TMap<FGameplayTag,TAttributeFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	UAuraAttributeSet();
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& Previous) const;
	
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Armor_Penetration(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Block_Chance(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Critical_Hit_Chance(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Critical_Hit_Damage(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Critical_Hit_Resistance(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Health_Regeneration(const FGameplayAttributeData& Previous) const;
	UFUNCTION()
	void OnRep_Mana_Regeneration(const FGameplayAttributeData& Previous) const;
	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	
	//primary attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Strength,Category="Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Intelligence,Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Resilience,Category="Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Vigor,Category="Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);
	
	//secondary attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Armor,Category="Primary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Armor_Penetration,Category="Primary Attributes")
	FGameplayAttributeData Armor_Penetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor_Penetration);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Block_Chance,Category="Primary Attributes")
	FGameplayAttributeData Block_Chance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Block_Chance);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Critical_Hit_Chance,Category="Primary Attributes")
	FGameplayAttributeData Critical_Hit_Chance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Critical_Hit_Chance);
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Critical_Hit_Damage,Category="Primary Attributes")
	FGameplayAttributeData Critical_Hit_Damage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Critical_Hit_Damage);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Critical_Hit_Resistance,Category="Primary Attributes")
	FGameplayAttributeData Critical_Hit_Resistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Critical_Hit_Resistance);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health_Regeneration,Category="Primary Attributes")
	FGameplayAttributeData Health_Regeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health_Regeneration);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana_Regeneration,Category="Primary Attributes")
	FGameplayAttributeData Mana_Regeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana_Regeneration);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data,FEffectProperties& Props) const;
};
