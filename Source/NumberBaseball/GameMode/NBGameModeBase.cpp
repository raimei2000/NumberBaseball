// NBGameModeBase.cpp


#include "GameMode/NBGameModeBase.h"

#include "Controller/NBPlayerController.h"
#include "Player/NBPlayerState.h"
#include "UI/UW_MainHUD.h"
#include "NumberBaseball.h"

#include "EngineUtils.h"

void ANBGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    ResetGame();
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

    NB_LOG_NET(LogNBNet, Error, TEXT("%d%d%d"), SecretNumber[0], SecretNumber[1], SecretNumber[2]);
}

void ANBGameModeBase::IncreaseGuessCount(ANBPlayerController* InPC)
{
    ANBPlayerState* NBPS = InPC->GetPlayerState<ANBPlayerState>();
    if (IsValid(NBPS))
    {
        NBPS->IncreaseGuessCount();

        if (NBPS->CurrentGuessCount >= NBPS->MaxGuessCount)
        {
            InPC->bOutOfChance = true;
        }
    }
}

TArray<int32> ANBGameModeBase::JudgeCommit(ANBPlayerController* CommitPlayerController, const TArray<int32>& InGuessNumber)
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

void ANBGameModeBase::JudgeGame(ANBPlayerController* CommitPlayerController, int32 InStrikeCount)
{
    if (InStrikeCount == 3) // CommitPlayerController Win
    {
        ANBPlayerState* NBPS = CommitPlayerController->GetPlayerState<ANBPlayerState>();
        FString ResultString = NBPS->PlayerNameString + FString(TEXT(" Win!!"));

        for (const auto& NBPC : AllPlayerControllers)
        {
            NBPC->ClientRPCShowGameResult(ResultString);
        }

        ResetGame();
    }
    else
    {
        bool bIsDraw = true;
        for (const auto& NBPC : AllPlayerControllers)
        {
            ANBPlayerState* NBPS = NBPC->GetPlayerState<ANBPlayerState>();
            if (NBPS->CurrentGuessCount < NBPS->MaxGuessCount)
            {
                bIsDraw = false;
                break;
            }
        }

        if (bIsDraw) // Draw
        {
            FString ResultString = FString::Printf(TEXT("Draw.. Answer: %d%d%d"), SecretNumber[0], SecretNumber[1], SecretNumber[2]);

            for (const auto& NBPC : AllPlayerControllers)
            {
                NBPC->ClientRPCShowGameResult(ResultString);
            }

            ResetGame();
        }
        else // Next Turn
        {
            MoveOnToNextTurn();
        }
    }
}

void ANBGameModeBase::ResetGame()
{
    InitSecretNumber();

    IndexOfPlayer = 0;

    for (TActorIterator<ANBPlayerController> It(GetWorld()); It; ++It)
    {
        (*It)->ClientRPCEnableNumberPad();
        (*It)->bOutOfChance = false;

        ANBPlayerState* NBPS = (*It)->GetPlayerState<ANBPlayerState>();
        if (IsValid(NBPS))
        {
            NBPS->CurrentGuessCount = 0;
            
        }
    }

    ControlTurn();
}

void ANBGameModeBase::ControlTurn()
{
    for (int32 i = 0; i < AllPlayerControllers.Num(); i++)
    {
        if (i == IndexOfPlayer)
        {
            AllPlayerControllers[i]->ClientRPCEnableNumberPad();
        }
        else
        {
            AllPlayerControllers[i]->ClientRPCDisableNumberPad();
        }
    }
}

void ANBGameModeBase::MoveOnToNextTurn()
{
    do
    {
        IndexOfPlayer++;
        IndexOfPlayer %= AllPlayerControllers.Num();
    } while (AllPlayerControllers[IndexOfPlayer]->bOutOfChance);

    ControlTurn();
}
