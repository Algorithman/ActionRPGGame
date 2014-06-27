// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "../ActionState/IARActionState.h"
#include "../Types/ARStructTypes.h"

#include "ARAbility.generated.h"

UCLASS(hidecategories = (Input, Movement, Collision, Rendering, "Utilities|Transformation"), MinimalAPI, Blueprintable, notplaceable)
class AARAbility : public AActor, public IIARActionState
{
	GENERATED_UCLASS_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;

	//Mainly used on server. To assign Owner properties;
	virtual void Initialize();

	UPROPERTY(Replicated)
	bool BlankRep;

	/* Currently Active weapon, must have any of these tags.
	If it doesn, then this ability can't be used **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FGameplayTagContainer WeaponRequiredTags;

	UPROPERTY(EditAnywhere, Category = "GUI")
		FSlateBrush AbilityIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Casting Speed")
		float CastingSpeed;

	UPROPERTY(EditAnywhere, Category = "Cost")
		TArray<FAttribute> ResourceCost;

	UPROPERTY()
	class AARCharacter* OwningCharacter;
	UPROPERTY()
	class AARPlayerController* OwiningController;
	UPROPERTY()
	class UARAttributeComponent* OwnerAttributes;
	UPROPERTY()
	class UAREquipmentComponent* OwnerEquipment;

	/* Checks if ability can be used with current weapon */
	bool CheckWeapon();
	/* Checks if owner have enough resources to use this ability */
	bool CheckResourceCost();

	/* [client] OVERIDE from IIARActionState */
	virtual void InputPressed() override;
	virtual void InputReleased() override;
	/*[Server]*/
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerStartAction();
	/*[Authorative]*/
	virtual void StartAction();

	/*
		These are client prediction helpers for drawing UI.
		They are purerly cosmetic, and do not affect gameplay,
		but they help with increasing smoothnes of gameplay,
		as player doesn't need to wait for notification from server about 
		various states of ability.
		Besides that, real state of ability is not directly accessible on client anyway.
		It's purerly server-side.
	*/
public:
	/*[Client Prediction]*/
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		float CurrentCastTime;
	/*[Client Prediction]*/
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		float CurrentCooldownTime;
	/*[Client Prediction]*/
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		bool IsOnCooldown;
	/*[Client Prediction]*/
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
		bool IsBeingUsed;
	/*
		Default action state component. All actions, like charing, shooting, casting, for
		weapons, abilities, and anything that need some kind of state handling
		will be done trough this component.
	*/
	/*[Replicated]*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		TSubobjectPtr<class UARActionStateComponent> ActionState;

};



