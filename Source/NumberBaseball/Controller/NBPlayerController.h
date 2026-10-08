// NBPlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NBPlayerController.generated.h"

class UUW_NumberPad;

/**
 * 
 */
UCLASS()
class NUMBERBASEBALL_API ANBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUW_NumberPad> NumberPadClass;

	TObjectPtr<UUW_NumberPad> NumberPadInstance;
};
