// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"

void AToonTanksModeBase::HandleActorDeath(AActor *deadActor)
{
	UE_LOG(LogTemp, Display, TEXT("deadPlayer"));
	if (!!deadActor && deadActor == tankPlayerRef)
	{
		tankPlayerRef->HandleDestruction();
		if (!!playerController)
		{
			playerController->SetPlayerController(false);
			GameOverActivate(false);
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("deadTurret"));
		ATurret *destroyedTower = Cast<ATurret>(deadActor);
		if (destroyedTower != nullptr)
		{
			destroyedTower->HandleDestruction();
			targetTowerNumber= targetTowerNumber-1;
			if(targetTowerNumber == 0)
				GameOverActivate(true);
		}
	}
}

void AToonTanksModeBase::BeginPlay()
{
	Super::BeginPlay();

	handleStart();
}

void AToonTanksModeBase::handleStart()
{
	targetTowerNumber = GetTargetTowerCount();
	tankPlayerRef = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	playerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	playerController->SetPlayerController(false);

	FTimerHandle playerEnableTimerHandle;

	FTimerDelegate playerEnableTimerDelegate = FTimerDelegate::CreateUObject(
		playerController,
		&AToonTanksPlayerController::SetPlayerController,
		true);

	GetWorldTimerManager().SetTimer(
		playerEnableTimerHandle,
		playerEnableTimerDelegate,
		playerStartRate,
		false);
}

int32 AToonTanksModeBase::GetTargetTowerCount()
{
	TArray<AActor *> turretArray;

	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), turretArray);

	return turretArray.Num();
}
