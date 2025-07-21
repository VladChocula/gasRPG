// Steven Oliveira


#include "Character/SUARPG_EnemyCharacter.h"
#include "SUARPG/SUARPG.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/Widget/SUARPG_UserWidget.h"
#include "AbilitySystem/AuraABSLibrary.h"
#include "SUARPG_AuraGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"

ASUARPG_EnemyCharacter::ASUARPG_EnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ASUARPG_EnemyCharacter::HighlightActor()
{
	
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void ASUARPG_EnemyCharacter::UnHighlightActor()
{

	GetMesh()->SetRenderCustomDepth(false);
	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(false);
	}
	
}

void ASUARPG_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();

	if (USUARPG_UserWidget* AUserWidget = Cast<USUARPG_UserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AUserWidget->SetWidgetController(this);
	}

	if (const UAuraAttributeSet* AAS = CastChecked<UAuraAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData Data) 
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		
		AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved)
			.AddUObject(
				this,
				&ASUARPG_EnemyCharacter::HitReactTagChanged
			);
		//Broadcast initial health and maxhealth values for the enemy
		OnHealthChanged.Broadcast(AAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AAS->GetMaxHealth());
	}
	
}

void ASUARPG_EnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;

	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void ASUARPG_EnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

int32 ASUARPG_EnemyCharacter::GetPlayerLevel()
{
	return Level;
}

void ASUARPG_EnemyCharacter::InitializeDefaultAttributes() const
{
	UAuraABSLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
