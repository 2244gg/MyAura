// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy: uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	NotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy: uint8
{
	RemoveOnOverlap,
	RemoveOnEndOverlap,
	NotRemove
};

UCLASS()
class MYAURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target,TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(EditAnywhere)
	EEffectApplicationPolicy InstantApplicationPolicy = EEffectApplicationPolicy::NotApply;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere)
	EEffectApplicationPolicy DurationApplicationPolicy = EEffectApplicationPolicy::NotApply;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UPROPERTY(EditAnywhere)
	EEffectApplicationPolicy InfiniteApplicationPolicy = EEffectApplicationPolicy::NotApply;
	UPROPERTY(EditAnywhere)
	EEffectRemovalPolicy InfiniteRemovalPolicy = EEffectRemovalPolicy::NotRemove;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveInfiniteEffectHandles;
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* Target);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* Target);
	
	
};
