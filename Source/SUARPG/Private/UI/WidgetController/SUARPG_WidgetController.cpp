// Steven Oliveira


#include "UI/WidgetController/SUARPG_WidgetController.h"

void USUARPG_WidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void USUARPG_WidgetController::BroadcastInitialValues()
{
	
}

void USUARPG_WidgetController::BindCallbacksToDependencies()
{

}
