// Fill out your copyright notice in the Description page of Project Settings.


#include "Charactors/CharacterImpl/AuraCharacter.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/AuraPlayerController.h"
#include "PlayerController/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch=false;
	bUseControllerRotationYaw=false;
	bUseControllerRotationRoll=false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilitySystemComponent();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilitySystemComponent();
}

void AAuraCharacter::InitAbilitySystemComponent()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet=AuraPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState,this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	if (AAuraPlayerController* AuraPlayerController=Cast<AAuraPlayerController>( GetController()))
	{
		if (AAuraHUD* HUD= Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			HUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
		
	}
}
