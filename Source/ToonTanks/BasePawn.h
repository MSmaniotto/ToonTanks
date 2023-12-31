// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	virtual void HandleDestruction();

protected:
	void RotateTurret(FVector targetPoint);

	void fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pawn Actor", meta=(AllowPrivateAccess="true"))
	class UCapsuleComponent* capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Pawn Actor", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* baseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Pawn Actor", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* turretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Pawn Actor", meta=(AllowPrivateAccess="true"))
	USceneComponent* projectileSpawnPoint;
	
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TSubclassOf<class AProjectile> projectile;

	UPROPERTY(EditAnywhere, Category="Pawn Actor")
	class UParticleSystem* deathParticles;

	UPROPERTY(EditAnywhere, Category="Pawn Actor")
	class USoundBase* deathSound;

	UPROPERTY(EditAnywhere, Category= "Pawn Actor")
	TSubclassOf<class UCameraShakeBase> deathCameraShakeClass;
};
