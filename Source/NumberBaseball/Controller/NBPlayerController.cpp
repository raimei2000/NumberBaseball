// NBPlayerController.cpp


#include "Controller/NBPlayerController.h"

#include "UI/UW_MainHUD.h"

void ANBPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (MainHUDWidgetClass)
    {
        MainHUDWidgetInstance = CreateWidget<UUW_MainHUD>(this, MainHUDWidgetClass);

        if (IsValid(MainHUDWidgetInstance))
        {
            MainHUDWidgetInstance->AddToViewport();
        }
    }

}
