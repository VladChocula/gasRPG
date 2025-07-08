// Steven Oliveira

#pragma once

#include "CoreMinimal.h"
#include "Character/SUARPG_BaseCharacter.h"
#include "Interaction/HighlightInterface.h"
#include "SUARPG_EnemyCharacter.generated.h"

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
	
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	/** Combat Interface **/
	virtual int32 GetPlayerLevel() override;

	/** End Combat Interface **/

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"), Category = "Character Class Defaults")
	int32 Level = 1;
};
