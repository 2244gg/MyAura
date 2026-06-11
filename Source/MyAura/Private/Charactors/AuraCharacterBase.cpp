// Fill out your copyright notice in the Description page of Project Settings.


#include "Charactors/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "DataWrappers/ChaosVDJointDataWrappers.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AAuraCharacterBase::InitializePrimaryAttributes()
{
	InitializeDefaultAttributes(DefaultPrimaryAttributes,1.f);
}

void AAuraCharacterBase::InitializeSecondaryAttributes()
{
	InitializeDefaultAttributes(DefaultSecondaryAttributes,1.f);
}

void AAuraCharacterBase::InitializeVitalAttributes()
{
	InitializeDefaultAttributes(DefaultVitalAttributes,1.f);
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::AddAbilities()
{
	UAuraAbilitySystemComponent* AuraASC=CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;
	AuraASC->AddCharacterAbilities(StartupAbilities);
	
}

void AAuraCharacterBase::InitializeDefaultAttributes(TSubclassOf<UGameplayEffect> DefaultAttributes, float level)
{
	check(GetAbilitySystemComponent());
	FGameplayEffectContextHandle ContextHandle=GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultAttributes,level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent());
}


