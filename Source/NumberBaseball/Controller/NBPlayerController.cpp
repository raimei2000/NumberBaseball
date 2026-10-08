// NBPlayerController.cpp


#include "Controller/NBPlayerController.h"

#include "UI/UW_NumberPad.h"

void ANBPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UUW_NumberPad* NumberPad = CreateWidget<UUW_NumberPad>(this, NumberPadClass);
    if (IsValid(NumberPad))
    {
        NumberPadInstance = NumberPad;
        NumberPadInstance->AddToViewport();
    }

}
