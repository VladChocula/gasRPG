// Steven Oliveira

#pragma once

#include "CoreMinimal.h"
#include "Character/SUARPG_BaseCharacter.h"
#include "SUARPG_AuraCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class SUARPG_API ASUARPG_AuraCharacter : public ASUARPG_BaseCharacter
{
	GENERATED_BODY()

public:
	ASUARPG_AuraCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface **/
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface **/

protected:

private:

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"), Category = "Camera")
	UCameraComponent* CameraComp;

	virtual void InitAbilityActorInfo() override;
};
