// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMana(25.f);
}

void UAuraAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	if (GetHealthAttribute()==Attribute)
	{
		NewValue=FMath::Clamp(NewValue,0.f,GetMaxHealth());
	}
	if (GetManaAttribute()==Attribute)
	{
		NewValue=FMath::Clamp(NewValue,0.f,GetMaxMana());
	}
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Props;
	SetEffectProperties(Data,Props);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Resilience,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Vigor,COND_None,REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor_Penetration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Block_Chance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Critical_Hit_Chance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Critical_Hit_Damage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Critical_Hit_Resistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health_Regeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana_Regeneration,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,Previous);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,Previous);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana,Previous);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMana,Previous);
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Strength,Previous);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Intelligence,Previous);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Resilience,Previous);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Vigor,Previous);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Armor,Previous);
}

void UAuraAttributeSet::OnRep_Armor_Penetration(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Armor_Penetration,Previous);
}

void UAuraAttributeSet::OnRep_Block_Chance(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Block_Chance,Previous);
}

void UAuraAttributeSet::OnRep_Critical_Hit_Chance(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Critical_Hit_Chance,Previous);
}

void UAuraAttributeSet::OnRep_Critical_Hit_Damage(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Critical_Hit_Damage,Previous);
}

void UAuraAttributeSet::OnRep_Critical_Hit_Resistance(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Critical_Hit_Resistance,Previous);
}

void UAuraAttributeSet::OnRep_Health_Regeneration(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health_Regeneration,Previous);
}

void UAuraAttributeSet::OnRep_Mana_Regeneration(const FGameplayAttributeData& Previous) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana_Regeneration,Previous);
}

void UAuraAttributeSet::SetEffectProperties(const struct FGameplayEffectModCallbackData& Data,FEffectProperties& Props) const
{
	Props.ContextHandle=Data.EffectSpec.GetContext();
	Props.SourceASC=Props.ContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC)&&Props.SourceASC->AbilityActorInfo.IsValid()&&Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor=Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController=Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController==nullptr&&Props.SourceAvatarActor!=nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController=Pawn->GetController();
			}
		}
	}
	if (Props.SourceController)
	{
		Props.SourceCharacter=Cast<ACharacter>(Props.SourceController->GetPawn());
	}
	if (Data.Target.AbilityActorInfo.IsValid()&&Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor=Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController=Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter=Cast<ACharacter>(Props.TargetController->GetPawn());
		Props.TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
