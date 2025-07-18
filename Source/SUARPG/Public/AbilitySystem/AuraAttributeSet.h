// Steven Oliveira

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "AuraAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class UAbilitySystemComponent;

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}
	
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	FGameplayEffectContextHandle EffectContextHandle;
};


// typedef is specific to the signature of FGameplayAttribute, but a static function pointer is generic to any
// signature chosen.
// typdef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class SUARPG_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

#pragma region VitalAttributes
UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
FGameplayAttributeData Health;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

UFUNCTION()
void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
FGameplayAttributeData Mana;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

UFUNCTION()
void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
#pragma endregion

#pragma region PrimaryAttributes
UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
FGameplayAttributeData Strength;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

UFUNCTION()
void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
FGameplayAttributeData Intelligence;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

UFUNCTION()
void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
FGameplayAttributeData Resilience;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

UFUNCTION()
void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
FGameplayAttributeData Vigor;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

UFUNCTION()
void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
#pragma endregion

#pragma region SecondaryAttributes
UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
FGameplayAttributeData MaxHealth;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

UFUNCTION()
void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
FGameplayAttributeData MaxMana;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

UFUNCTION()
void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
FGameplayAttributeData Armor;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
UFUNCTION()
void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
FGameplayAttributeData ArmorPenetration;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);
UFUNCTION()
void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
FGameplayAttributeData BlockChance;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);
UFUNCTION()
void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritHitChance, Category = "Secondary Attributes")
FGameplayAttributeData CritHitChance;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritHitChance);
UFUNCTION()
void OnRep_CritHitChance(const FGameplayAttributeData& OldCritHitChance) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritHitDamage, Category = "Secondary Attributes")
FGameplayAttributeData CritHitDamage;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritHitDamage);
UFUNCTION()
void OnRep_CritHitDamage(const FGameplayAttributeData& OldCritHitDamage) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritHitResistance, Category = "Secondary Attributes")
FGameplayAttributeData CritHitResistance;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CritHitResistance);
UFUNCTION()
void OnRep_CritHitResistance(const FGameplayAttributeData& OldCritHitResistance) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegen, Category = "Secondary Attributes")
FGameplayAttributeData HealthRegen;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegen);
UFUNCTION()
void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const;

UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegen, Category = "Secondary Attributes")
FGameplayAttributeData ManaRegen;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegen);
UFUNCTION()
void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const;
#pragma endregion

#pragma region MetaAttributes
UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes") 
FGameplayAttributeData IncDamage;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncDamage);
#pragma endregion


private:
	
	const void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& OutEffectProps);
};
