// Steven Oliveira

#pragma once

#include "CoreMinimal.h"
#include "Character/SUARPG_BaseCharacter.h"
#include "Interaction/HighlightInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "SUARPG_EnemyCharacter.generated.h"


class UWidgetComponent;
/**
 * 
 */
UCLASS()
class SUARPG_API ASUARPG_EnemyCharacter : public ASUARPG_BaseCharacter, public IHighlightInterface
{
	GENERATED_BODY()

public:
	ASUARPG_EnemyCharacter();

	// Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//End Enemy Interface

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	/** Combat Interface **/
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface **/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"), Category = "Character Class Defaults")
	int32 Level = 1;
};
