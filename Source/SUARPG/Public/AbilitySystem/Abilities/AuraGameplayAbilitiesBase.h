// Steven Oliveira

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbilitiesBase.generated.h"

/**
 * 
 */
UCLASS()
class SUARPG_API UAuraGameplayAbilitiesBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
};
