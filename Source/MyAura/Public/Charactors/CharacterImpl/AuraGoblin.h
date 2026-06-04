// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Charactors/AuraEnemy.h"
#include "AuraGoblin.generated.h"

/**
 * 
 */
UCLASS()
class MYAURA_API AAuraGoblin : public AAuraEnemy
{
	GENERATED_BODY()
	public:
	virtual void HighLightAction() override;
	virtual void UnHighLightAction() override;
};
