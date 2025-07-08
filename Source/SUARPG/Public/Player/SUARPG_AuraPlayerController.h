// Steven Oliveira

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "SUARPG_AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IHighlightInterface;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;
class USplineComponent;

/**
 * 
 */
UCLASS()
class SUARPG_API ASUARPG_AuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASUARPG_AuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override; 

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	//Utility that returns that sets the AbilitySystemComponent on First Call and returns it after.
	UAuraAbilitySystemComponent* GetASC();

	void Move(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	//Highlighting Functionality
	void CursorTrace();
	TScriptInterface<IHighlightInterface> lastActor;
	TScriptInterface<IHighlightInterface> thisActor;

	/*Click To Move Implementation*/
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargetting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	//This is the smooth path created between you clicking a point and your character moving to it
	UPROPERTY(VisibleAnywhere) 
	TObjectPtr<USplineComponent> Spline; 
	/* End Click to Move Implementation functionality*/

};
