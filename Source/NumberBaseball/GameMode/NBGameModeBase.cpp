// NBGameModeBase.cpp


#include "GameMode/NBGameModeBase.h"

#include "Controller/NBPlayerController.h"
#include "Player/NBPlayerState.h"

void ANBGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    InitSecretNumber();
}

void ANBGameModeBase::OnPostLogin(AController* NewPlayer)
{
    Super::OnPostLogin(NewPlayer);

    ANBPlayerController* NBPC = Cast<ANBPlayerController>(NewPlayer);
    if (IsValid(NBPC))
    {
        AllPlayerControllers.Add(NBPC);

        ANBPlayerState* NBPS = NBPC->GetPlayerState<ANBPlayerState>();
        if (IsValid(NBPS))
        {
            NBPS->PlayerNameString = TEXT("Player") + FString::FromInt(AllPlayerControllers.Num());
        }
    }
}

void ANBGameModeBase::InitSecretNumber()
{
    TArray<int32> Digits;
    for (int32 i = 1; i <= 9; ++i)
    {
        Digits.Add(i);
    }

    SecretNumber.Reset(NumberOfDigit);
    for (int32 i = 0; i < NumberOfDigit; ++i)
    {
        int32 Index = FMath::RandRange(0, Digits.Num() - 1);
        SecretNumber.Add(Digits[Index]);
        Digits.RemoveAt(Index);
    }
}

void ANBGameModeBase::IncreaseGuessCount(ANBPlayerController* InPC)
{
    ANBPlayerState* NBPS = InPC->GetPlayerState<ANBPlayerState>();
    if (IsValid(NBPS))
    {
        NBPS->IncreaseGuessCount();
    }
}

TArray<int32> ANBGameModeBase::JudgeResult(ANBPlayerController* CommitPlayerController, const TArray<int32>& InGuessNumber)
{
    TArray<int32> Result = { 0, 0, 0 };

    for (int32 i = 0; i < InGuessNumber.Num(); ++i)
    {
        if (SecretNumber[i] == InGuessNumber[i])
        {
            Result[1]++; // StrikeCount
        }
        else if (SecretNumber.Contains(InGuessNumber[i]))
        {
            Result[0]++; // BallCount
        }
    }

    if (Result[0] == 0 && Result[1] == 0)
    {
        Result[2]++;
    }

    IncreaseGuessCount(CommitPlayerController);

    return Result;
}
