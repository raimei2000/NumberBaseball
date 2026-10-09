// NBGameModeBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NBGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NUMBERBASEBALL_API ANBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay()override;

public:
	void InitSecretNumber();

	// Return Array: [Ball, Strike, Out]
	TArray<int32> JudgeResult(const TArray<int32>& InGuessNumber);

private:
	int32 NumberOfDigit = 3;

	TArray<int32> SecretNumber;
};
