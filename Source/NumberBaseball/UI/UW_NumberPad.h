// UW_NumberPad.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_NumberPad.generated.h"

class UHorizontalBox;
class UUW_NumberButton;

/**
 * 
 */
UCLASS()
class NUMBERBASEBALL_API UUW_NumberPad : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> ButtonContainer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUW_NumberButton> ButtonClass;
};
