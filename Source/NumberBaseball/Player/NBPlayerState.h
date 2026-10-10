// NBPlayerState.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NBPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NUMBERBASEBALL_API ANBPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ANBPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	void IncreaseGuessCount();

	UFUNCTION()
	void OnRep_UpdateCurrentGuessCountText();

public:
	UPROPERTY(Replicated)
	FString PlayerNameString;

	UPROPERTY(ReplicatedUsing = OnRep_UpdateCurrentGuessCountText)
	int32 CurrentGuessCount;

	UPROPERTY(Replicated)
	int32 MaxGuessCount;
};
