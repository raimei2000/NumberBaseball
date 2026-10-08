// UW_NumberButton.cpp


#include "UI/UW_NumberButton.h"

#include "Components/Button.h"

void UUW_NumberButton::NativeConstruct()
{
    if (false == NumberButton->OnClicked.IsAlreadyBound(this, &UUW_NumberButton::HandleButtonClicked))
    {
        NumberButton->OnClicked.AddDynamic(this, &UUW_NumberButton::HandleButtonClicked);
    }
}

void UUW_NumberButton::NativeDestruct()
{
    if (true == NumberButton->OnClicked.IsAlreadyBound(this, &UUW_NumberButton::HandleButtonClicked))
    {
        NumberButton->OnClicked.RemoveDynamic(this, &UUW_NumberButton::HandleButtonClicked);
    }
}

void UUW_NumberButton::HandleButtonClicked()
{
    OnNumButtonClicked.Broadcast(Digit);
}

void UUW_NumberButton::SetDigit(int32 InDigit)
{
    Digit = InDigit;
}
