// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Charactors/AuraCharacterBase.h"
#include "Interaction/IHighLightInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYAURA_API AAuraEnemy : public AAuraCharacterBase,public IIHighLightInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	virtual void BeginPlay() override;
	virtual void HighLightAction() override;
	virtual void UnHighLightAction() override;
};
