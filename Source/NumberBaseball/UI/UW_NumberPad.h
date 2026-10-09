// UW_NumberPad.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_NumberPad.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChosenNumberChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNumberCommittedDelegate, const TArray<int32>&, Digits);

class UWrapBox;
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

	UFUNCTION()
	void HandleEnterButtonClicked();

#pragma endregion

#pragma region Delegate

public:
	FOnChosenNumberChangedDelegate OnChosenNumberChanged;

	FOnNumberCommittedDelegate OnNumberCommitted;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWrapBox> ButtonContainer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUW_NumberButton> ButtonClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackSpaceButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EnterButton;

#pragma endregion

#pragma region Fields

public:
	UPROPERTY()
	TArray<TObjectPtr<UUW_NumberButton>> NumberButtons;

	UPROPERTY()
	TArray<int32> Digits;

private:
	int32 MaxNumberOfDigits = 3;

#pragma endregion
};
