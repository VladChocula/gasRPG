// Steven Oliveira


#include "AbilitySystem/AuraABSLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/SUARPG_HUD.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/SUARPG_WidgetController.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SUARPG_GameModeBase.h"
#include "AbilitySystemComponent.h"

UOverlayWidgetController* UAuraABSLibrary::GetOverlayWidgetController(const UObject* WorldContextObj)
{

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObj, 0))
	{
		if (ASUARPG_HUD* AuraHUD = Cast<ASUARPG_HUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAttributeSet* AAS = PS->GetAttributeSet();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AAS);
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UAuraABSLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObj)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObj, 0))
	{
		if (ASUARPG_HUD* AuraHUD = Cast<ASUARPG_HUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAttributeSet* AAS = PS->GetAttributeSet();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AAS);
			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

void UAuraABSLibrary::InitializeDefaultAttributes(const UObject* WorldContextObj, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	ASUARPG_GameModeBase* AGameMode = Cast<ASUARPG_GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObj));
	if (AGameMode == nullptr) return;

	AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = AGameMode->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo = AGameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
	
	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpechandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpechandle.Data.Get());
}
