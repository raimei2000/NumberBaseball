// NBGameModeBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NBGameModeBase.generated.h"

class ANBPlayerController;

/**
 * 
 */
UCLASS()
class NUMBERBASEBALL_API ANBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay()override;

	virtual void OnPostLogin(AController* NewPlayer) override;

public:
	void InitSecretNumber();

	void IncreaseGuessCount(ANBPlayerController* InPC);

	// Return Array: [Ball, Strike, Out]
	TArray<int32> JudgeResult(ANBPlayerController* CommitPlayerController, const TArray<int32>& InGuessNumber);

private:
	int32 NumberOfDigit = 3;

	TArray<int32> SecretNumber;

	UPROPERTY()
	TArray<TObjectPtr<ANBPlayerController>> AllPlayerControllers;
};
