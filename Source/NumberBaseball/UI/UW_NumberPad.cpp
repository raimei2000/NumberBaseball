// UW_NumberPad.cpp


#include "UI/UW_NumberPad.h"

#include "UI/UW_NumberButton.h"

#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UUW_NumberPad::NativeConstruct()
{
    Super::NativeConstruct();

    for (int32 i = 1; i <= 9; ++i)
    {
        UUW_NumberButton* Button = CreateWidget<UUW_NumberButton>(this, ButtonClass);
        Button->SetDigit(i);
        Button->NumberText->SetText(FText::FromString(FString::Printf(TEXT("%d"), i)));
        Button->OnNumButtonClicked.AddDynamic(this, &UUW_NumberPad::HandleNumberButtonClicked);

        ButtonContainer->AddChildToHorizontalBox(Button);
        NumberButtons.Add(Button);
    }
}

void UUW_NumberPad::NativeDestruct()
{
    Super::NativeDestruct();
}

void UUW_NumberPad::HandleNumberButtonClicked(int32 Digit)
{
    // 숫자 1 ~ 9, NumberButtons에는 0 ~ 8
    int32 ArrayIndex = Digit - 1;

    if (NumberButtons.IsValidIndex(ArrayIndex))
    {
        NumberButtons[ArrayIndex]->SetIsEnabled(false);
    }

}
