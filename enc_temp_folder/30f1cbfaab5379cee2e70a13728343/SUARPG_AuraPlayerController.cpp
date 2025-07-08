// Steven Oliveira


#include "Player/SUARPG_AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/HighlightInterface.h"
#include "Input/AuraInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "SUARPG_AuraGameplayTags.h"

ASUARPG_AuraPlayerController::ASUARPG_AuraPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ASUARPG_AuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void ASUARPG_AuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	
	if (!CursorHit.bBlockingHit) return;

	lastActor = thisActor;
	thisActor = CursorHit.GetActor();

	/**
	*Line trace from cursor. Several scenarios:
	*A. lastActor is null && thisActor is null
	*	-Do nothing.
	*B. lastActor is null && thisActor is valid
	*	- highlight thisActor
	*C. lastActor is valid && thisActor is null
	*	- UnHighlight lastActor
	*D. lastActor is valid && thisActor is Valid, but lastActor != thisActor
	*	- UnHighlight lastActor, highlight thisActor
	*E. lastActor && thisActor is valid, and lastActor == thisActor
	*	- Do nothing
	*/

	if (lastActor == nullptr)
	{
		if (thisActor != nullptr)
		{
			thisActor->HighlightActor();
		}
	}
	else
	{
		if (thisActor == nullptr)
		{
			lastActor->UnHighlightActor();
		}
		else
		{
			if (lastActor != thisActor)
			{
				lastActor->UnHighlightActor();
				thisActor->HighlightActor();
			}
		}
	}

}

void ASUARPG_AuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	//Use an if based check instead of check due to this being a multiplayer title.
	if (Subsystem) { Subsystem->AddMappingContext(AuraContext, 0); }

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}
	
void ASUARPG_AuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);

	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASUARPG_AuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

UAuraAbilitySystemComponent* ASUARPG_AuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return AuraAbilitySystemComponent;
}

void ASUARPG_AuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDir, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDir, InputAxisVector.X);
	}
}

void ASUARPG_AuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargetting = thisActor == nullptr ? true : false;
		bAutoRunning = false;
	}
	
}

void ASUARPG_AuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ASUARPG_AuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{

	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)) //Fire off whatever ability was assigned to LMB hold
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
			
		}
		return;
	}
	
	if (bTargetting) //We are clicking on an enemy, so fire off a held gameplay ability
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

