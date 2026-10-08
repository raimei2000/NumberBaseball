// UW_MainHUD.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_MainHUD.generated.h"

class UUW_NumberPad;
class UTextBlock;

/**
 * 
 */
UCLASS()
class NUMBERBASEBALL_API UUW_MainHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

public:
	UFUNCTION()
	void HandleChosenNumberChanged();

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUW_NumberPad> NumberPad;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ChosenNumberText;

};
