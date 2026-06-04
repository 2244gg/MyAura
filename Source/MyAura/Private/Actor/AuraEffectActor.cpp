// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootSceneComponent"));
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC==nullptr) return;
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle=TargetASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle=TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.f,ContextHandle);
	FActiveGameplayEffectHandle EffectHandle=TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	bool bIsInfinite=SpecHandle.Data.Get()->Def.Get()->DurationPolicy==EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteRemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveInfiniteEffectHandles.Add(EffectHandle,TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* Target)
{
	if (InstantApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(Target, InstantGameplayEffectClass);
	}
	if (DurationApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(Target, DurationGameplayEffectClass);
	}
	if (InfiniteApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(Target, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* Target)
{
	if (InstantApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(Target, InstantGameplayEffectClass);
	}
	if (DurationApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(Target, DurationGameplayEffectClass);
	}
	if (InfiniteApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(Target, InfiniteGameplayEffectClass);
	}
	if (InfiniteRemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
		if (!IsValid(TargetASC)) return;
		
		TArray<FActiveGameplayEffectHandle> HandlesToDel;
		for (auto HandlePair:ActiveInfiniteEffectHandles)
		{
			if (TargetASC==HandlePair.Value)
			{
				HandlesToDel.Add(HandlePair.Key);
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);
			}
		}
		for (auto& Handle:HandlesToDel)
		{
			ActiveInfiniteEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}


