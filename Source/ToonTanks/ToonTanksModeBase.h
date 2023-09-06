// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksModeBase.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API AToonTanksModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void HandleActorDeath(AActor *deadActor);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameOverActivate(bool bWonGame);

private:
	class ATank *tankPlayerRef;
	class AToonTanksPlayerController *playerController;

	float playerStartRate = 3.0f;

	void handleStart();

	int32 targetTowerNumber = 0;
	int32 GetTargetTowerCount();
};
