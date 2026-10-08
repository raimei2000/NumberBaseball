// UW_NumberPad.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_NumberPad.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChosenNumberChangedDelegate);

class UHorizontalBox;
class UUW_NumberButton;
class UButton;

/**
 * 
 */
UCLASS()
class NUMBERBASEBALL_API UUW_NumberPad : public UUserWidget
{
	GENERATED_BODY()

#pragma region Lifecycle Override

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

#pragma endregion

#pragma region EventHandler

private:
	UFUNCTION()
	void HandleNumberButtonClicked(int32 Digit);

	UFUNCTION()
	void DeleteLastDigit();

#pragma endregion

#pragma region Delegate

public:
	FOnChosenNumberChangedDelegate OnChosenNumberChanged;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> ButtonContainer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUW_NumberButton> ButtonClass;

	UPROPERTY()
	TArray<TObjectPtr<UUW_NumberButton>> NumberButtons;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackSpaceButton;

#pragma endregion

#pragma region Fields

public:
	UPROPERTY()
	TArray<int32> Digits;

private:
	int32 MaxNumberOfDigits = 3;

#pragma endregion
};
