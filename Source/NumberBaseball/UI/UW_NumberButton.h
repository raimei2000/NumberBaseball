// UW_NumberButton.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_NumberButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNumButtonClickedDelegate, int32, Digit);

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class NUMBERBASEBALL_API UUW_NumberButton : public UUserWidget
{
	GENERATED_BODY()

#pragma region Lifecycle Override

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

#pragma endregion

#pragma region Func

private:
	UFUNCTION()
	void HandleButtonClicked();

#pragma endregion

#pragma region Setter/Getter

public:
	void SetDigit(int32 InDigit);

	FORCEINLINE int32 GetDigit() const { return Digit; }

#pragma endregion

#pragma region Delegate

public:
	FOnNumButtonClickedDelegate OnNumButtonClicked;

#pragma endregion

#pragma region Field

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UButton> NumberButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> NumberText;

private:
	int32 Digit;

#pragma endregion
	
};
