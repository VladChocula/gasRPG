// Steven Oliveira

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SUARPG_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUARPG_API USUARPG_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<UObject> WidgetController;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
