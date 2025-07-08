// Steven Oliveira


#include "UI/Widget/SUARPG_UserWidget.h"

void USUARPG_UserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
