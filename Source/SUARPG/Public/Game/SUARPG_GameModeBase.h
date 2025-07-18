// Steven Oliveira

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SUARPG_GameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class SUARPG_API ASUARPG_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
	
};
