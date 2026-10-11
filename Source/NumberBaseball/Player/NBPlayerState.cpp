// NBPlayerState.cpp


#include "NBPlayerState.h"

#include "Controller/NBPlayerController.h"
#include "UI/UW_MainHUD.h"

#include "Net/UnrealNetwork.h"

ANBPlayerState::ANBPlayerState()
    : PlayerNameString(TEXT("None"))
    , CurrentGuessCount(0)
    , MaxGuessCount(5)
{
    bReplicates = true;
}

void ANBPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, PlayerNameString);
    DOREPLIFETIME(ThisClass, CurrentGuessCount);
    DOREPLIFETIME(ThisClass, MaxGuessCount);
}

void ANBPlayerState::IncreaseGuessCount()
{
    CurrentGuessCount++;
}

void ANBPlayerState::OnRep_UpdateCurrentGuessCountText()
{
    if (HasAuthority()) { return; }

    ANBPlayerController* NBPC = Cast<ANBPlayerController>(GetOwningController());
    if (IsValid(NBPC))
    {
        NBPC->MainHUDWidgetInstance->UpdateGuessCountText();
    }
}
