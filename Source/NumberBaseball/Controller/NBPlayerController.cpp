// NBPlayerController.cpp


#include "Controller/NBPlayerController.h"

#include "NumberBaseball.h"
#include "UI/UW_MainHUD.h"
#include "UI/UW_NumberPad.h"

#include "EngineUtils.h"

ANBPlayerController::ANBPlayerController()
{
    bReplicates = true;
}

void ANBPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (!IsLocalController()) { return; }

    FInputModeUIOnly InputModeUIOnly;
    SetInputMode(InputModeUIOnly);

    if (MainHUDWidgetClass)
    {
        MainHUDWidgetInstance = CreateWidget<UUW_MainHUD>(this, MainHUDWidgetClass);

        if (IsValid(MainHUDWidgetInstance))
        {
            MainHUDWidgetInstance->AddToViewport();
            MainHUDWidgetInstance->NumberPad->OnNumberCommitted.AddDynamic(this, &ANBPlayerController::HandleNumberCommit);
        }
    }

}

void ANBPlayerController::HandleNumberCommit(const TArray<int32>& InDigits)
{
    ServerRPCLogChosenNumber(InDigits);
}

void ANBPlayerController::ServerRPCLogChosenNumber_Implementation(const TArray<int32>& InDigits)
{
    int32 Number = 0;
    for (int32 Digit : InDigits)
    {
        Number = Number * 10 + Digit;
    }

    for (TActorIterator<ANBPlayerController> It(GetWorld()); It; ++It)
    {
        ANBPlayerController* NBPC = *It;
        if (IsValid(NBPC))
        {
            NBPC->ClientRPCLogChosenNumber(FString::FromInt(Number));
        }
    }
}

void ANBPlayerController::ClientRPCLogChosenNumber_Implementation(const FString& InNumberString)
{
    NB_LOG_NET(LogNBNet, Log, TEXT("%s"), *InNumberString);
}
