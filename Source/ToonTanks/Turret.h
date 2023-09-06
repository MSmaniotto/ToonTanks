// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank *tank;

	FTimerHandle timerHandle;

	float fireRate = 2.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float range = 300.f;

	bool CheckFireCondition();
	void triggerFire();
};
