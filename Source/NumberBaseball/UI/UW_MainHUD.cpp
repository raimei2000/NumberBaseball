// UW_MainHUD.cpp


#include "UI/UW_MainHUD.h"

#include "UI/UW_NumberPad.h"

#include "Components/TextBlock.h"

void UUW_MainHUD::NativeConstruct()
{
    Super::NativeConstruct();

    if (false == NumberPad->OnChosenNumberChanged.IsAlreadyBound(this, &UUW_MainHUD::HandleChosenNumberChanged))
    {
        NumberPad->OnChosenNumberChanged.AddDynamic(this, &UUW_MainHUD::HandleChosenNumberChanged);
    }
}

void UUW_MainHUD::NativeDestruct()
{
    if (true == NumberPad->OnChosenNumberChanged.IsAlreadyBound(this, &UUW_MainHUD::HandleChosenNumberChanged))
    {
        NumberPad->OnChosenNumberChanged.RemoveDynamic(this, &UUW_MainHUD::HandleChosenNumberChanged);
    }

    Super::NativeDestruct();
}

void UUW_MainHUD::HandleChosenNumberChanged()
{
    int32 NewNumber = 0;
    for (int32 Digit : NumberPad->Digits)
    {
        NewNumber = NewNumber * 10 + Digit;
    }

    ChosenNumberText->SetText(FText::AsNumber(NewNumber));
}
