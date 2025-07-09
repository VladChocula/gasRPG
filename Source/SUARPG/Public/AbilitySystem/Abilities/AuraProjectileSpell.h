// Steven Oliveira

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbilitiesBase.h"
#include "AuraProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class SUARPG_API UAuraProjectileSpell : public UAuraGameplayAbilitiesBase
{
	GENERATED_BODY()
	
protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
