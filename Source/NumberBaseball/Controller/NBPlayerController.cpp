// NBPlayerController.cpp


#include "Controller/NBPlayerController.h"

#include "NumberBaseball.h"
#include "UI/UW_MainHUD.h"
#include "UI/UW_NumberPad.h"
#include "GameMode/NBGameModeBase.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

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
    ServerRPCHandleCommit(InDigits);
}

void ANBPlayerController::ServerRPCHandleCommit_Implementation(const TArray<int32>& InDigits)
{
    AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
    if (IsValid(GM))
    {
        ANBGameModeBase* NBGM = Cast<ANBGameModeBase>(GM);
        if (IsValid(NBGM))
        {
            TArray<int32> ResultArray = NBGM->JudgeResult(this, InDigits);

            for (TActorIterator<ANBPlayerController> It(GetWorld()); It; ++It)
            {
                ANBPlayerController* NBPC = *It;
                if (IsValid(NBPC))
                {
                    NBPC->ClientRPCUpdateResultText(InDigits, ResultArray);
                }
            }
        }
    }
}

void ANBPlayerController::ClientRPCUpdateResultText_Implementation(const TArray<int32>& GuessArray, const TArray<int32>& ResultArray)
{
    MainHUDWidgetInstance->UpdateResultText(GuessArray, ResultArray);
    MainHUDWidgetInstance->UpdateGuessCountText();
}
