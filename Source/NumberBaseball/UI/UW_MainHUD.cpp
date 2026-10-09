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

    ChosenNumberText->SetText(FText::AsNumber(0));
    ResultText->SetText(FText::FromString(TEXT("")));
}

void UUW_MainHUD::NativeDestruct()
{
    if (true == NumberPad->OnChosenNumberChanged.IsAlreadyBound(this, &UUW_MainHUD::HandleChosenNumberChanged))
    {
        NumberPad->OnChosenNumberChanged.RemoveDynamic(this, &UUW_MainHUD::HandleChosenNumberChanged);
    }

    Super::NativeDestruct();
}

void UUW_MainHUD::UpdateResultText(const TArray<int32>& GuessArray, const TArray<int32>& ResultArray)
{
    // [Ball, Strike, Out]
    if (ResultArray.Num() != 3) { return; }

    int32 GuessNumber = 0;
    for (int32 Digit : GuessArray)
    {
        GuessNumber = GuessNumber * 10 + Digit;
    }

    FText Result;
    if (ResultArray[2] > 0) // Out
    {
        Result = FText::FromString(TEXT("Out"));
    }
    else // N Ball M Strike
    {
        Result = FText::FromString(FString::Printf(TEXT("%d => %dB %dS"), GuessNumber, ResultArray[0], ResultArray[1]));
    }

    ResultText->SetText(Result);
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
