// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHighLightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIHighLightInterface : public UInterface
{
	GENERATED_BODY()
	
	
};

/**
 * 
 */
class MYAURA_API IIHighLightInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HighLightAction()=0;
	virtual void UnHighLightAction()=0;
};
