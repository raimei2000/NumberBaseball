// UW_NumberButton.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_NumberButton.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class NUMBERBASEBALL_API UUW_NumberButton : public UUserWidget
{
	GENERATED_BODY()

public:

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> NumberButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> NumberText;
	
};
