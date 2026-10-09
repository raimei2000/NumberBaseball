// NBPlayerState.cpp


#include "NBPlayerState.h"

#include "Net/UnrealNetwork.h"

ANBPlayerState::ANBPlayerState()
    : PlayerNameString(TEXT("None"))
    , CurrentGuessCount(0)
    , MaxGuessCount(10)
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
