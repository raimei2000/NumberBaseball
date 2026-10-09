// NBPlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NBPlayerController.generated.h"

class UUW_MainHUD;

/**
 * 
 */
UCLASS()
class NUMBERBASEBALL_API ANBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANBPlayerController();

	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleNumberCommit(const TArray<int32>& InDigits);

	UFUNCTION(Server, Reliable)
	void ServerRPCHandleCommit(const TArray<int32>& InDigits);

	UFUNCTION(Client, Reliable)
	void ClientRPCUpdateResultText(const TArray<int32>& GuessArray, const TArray<int32>& ResultArray);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUW_MainHUD> MainHUDWidgetClass;

	TObjectPtr<UUW_MainHUD> MainHUDWidgetInstance;
};
