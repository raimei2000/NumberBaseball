// NBGameStateBase.cpp


#include "GameState/NBGameStateBase.h"

#include "Net/UnrealNetwork.h"

ANBGameStateBase::ANBGameStateBase()
{
    bReplicates = true;
}

void ANBGameStateBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, NumberOfPlayers);
}
