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
        Button->NumberText->SetText(FText::FromString(FString::Printf(TEXT("%d"), i)));
        ButtonContainer->AddChildToHorizontalBox(Button);
    }
}

void UUW_NumberPad::NativeDestruct()
{
    Super::NativeDestruct();
}
