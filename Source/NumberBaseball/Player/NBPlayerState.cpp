// NBPlayerState.cpp


#include "NBPlayerState.h"

#include "Net/UnrealNetwork.h"

ANBPlayerState::ANBPlayerState()
    : PlayerNameString(TEXT("None"))
{
    bReplicates = true;
}

void ANBPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, PlayerNameString);
}
