// NBPlayerController.cpp


#include "Controller/NBPlayerController.h"

#include "NumberBaseball.h"
#include "UI/UW_MainHUD.h"
#include "UI/UW_NumberPad.h"
#include "GameMode/NBGameModeBase.h"
#include "Player/NBPlayerState.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

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
    ANBPlayerState* NBPS = GetPlayerState<ANBPlayerState>();
    if (NBPS->CurrentGuessCount + 1 == NBPS->MaxGuessCount)
    {
        MainHUDWidgetInstance->NumberPad->SetIsEnabled(false);
    }

    ServerRPCHandleCommit(InDigits);
}

void ANBPlayerController::ClientRPCEnableNumberPad_Implementation()
{
    MainHUDWidgetInstance->NumberPad->SetIsEnabled(true);
}

void ANBPlayerController::ClientRPCShowGameResult_Implementation(const FString& InResultString)
{
    MainHUDWidgetInstance->NotificationText->SetText(FText::FromString(InResultString));
}

void ANBPlayerController::ServerRPCHandleCommit_Implementation(const TArray<int32>& InDigits)
{
    AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
    if (IsValid(GM))
    {
        ANBGameModeBase* NBGM = Cast<ANBGameModeBase>(GM);
        if (IsValid(NBGM))
        {
            TArray<int32> ResultArray = NBGM->JudgeCommit(this, InDigits);

            for (TActorIterator<ANBPlayerController> It(GetWorld()); It; ++It)
            {
                ANBPlayerController* NBPC = *It;
                if (IsValid(NBPC))
                {
                    NBPC->ClientRPCUpdateResultText(InDigits, ResultArray);
                }
            }

            NBGM->JudgeGame(this, ResultArray[1]);
        }
    }
}

void ANBPlayerController::ClientRPCUpdateResultText_Implementation(const TArray<int32>& GuessArray, const TArray<int32>& ResultArray)
{
    MainHUDWidgetInstance->UpdateResultText(GuessArray, ResultArray);
}
