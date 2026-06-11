// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"


UCLASS()
class MYAURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass,typename PressedFuncType,typename HeldFuncType,typename ReleasedFuncType>
	void bindAbilityAction(const UAuraInputConfig* Config,UserClass* Object,PressedFuncType PressedFunc,HeldFuncType HeldFunc,ReleasedFuncType ReleasedFunc);
};

template <class UserClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType>
void UAuraInputComponent::bindAbilityAction(const UAuraInputConfig* Config, UserClass* Object,
	PressedFuncType PressedFunc, HeldFuncType HeldFunc, ReleasedFuncType ReleasedFunc)
{
	
	for (const FAuraInputAction& Action :Config->AbilityInputActions)
	{
		if (Action.InputAction&&Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressedFunc,Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
			}
		}
	}
}
