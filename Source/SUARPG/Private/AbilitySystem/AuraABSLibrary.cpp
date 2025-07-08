// Steven Oliveira


#include "AbilitySystem/AuraABSLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/SUARPG_HUD.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/SUARPG_WidgetController.h"

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
