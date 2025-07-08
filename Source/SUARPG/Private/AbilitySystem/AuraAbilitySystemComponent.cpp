// Steven Oliveira


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "SUARPG_AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbilitiesBase.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);

		if (const UAuraGameplayAbilitiesBase* AuraAbility = Cast<UAuraGameplayAbilitiesBase>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}

		
		
		//GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer OutTagContainer;
	EffectSpec.GetAllAssetTags(OutTagContainer);
	EffectAssetTags.Broadcast(OutTagContainer);
}
