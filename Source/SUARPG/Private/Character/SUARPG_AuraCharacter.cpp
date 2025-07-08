// Steven Oliveira


#include "Character/SUARPG_AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/SUARPG_AuraPlayerController.h"
#include "UI/HUD/SUARPG_HUD.h"

ASUARPG_AuraCharacter::ASUARPG_AuraCharacter()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);


	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ASUARPG_AuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();

}

void ASUARPG_AuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor info for the client.
	InitAbilityActorInfo();
}

int32 ASUARPG_AuraCharacter::GetPlayerLevel()
{
	const AAuraPlayerState* aPlayerState = GetPlayerState<AAuraPlayerState>();
	check(aPlayerState);
	return aPlayerState->GetPlayerLevel();
}

void ASUARPG_AuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* aPlayerState = GetPlayerState<AAuraPlayerState>();
	check(aPlayerState);
	aPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(aPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(aPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = aPlayerState->GetAbilitySystemComponent();
	AttributeSet = aPlayerState->GetAttributeSet();

	// doing an if-based check on the cast, because in multiplayer, the APC will be null on other user's clients.
	if (ASUARPG_AuraPlayerController* APC = Cast<ASUARPG_AuraPlayerController>(GetController()))
	{
		if (ASUARPG_HUD* PlayerHUD = Cast<ASUARPG_HUD>(APC->GetHUD()))
		{
			PlayerHUD->InitOverlay(APC, aPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}
