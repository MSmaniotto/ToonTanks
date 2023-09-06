// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float damage = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	UStaticMeshComponent *baseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	class UProjectileMovementComponent *projectileMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *hitComp, AActor *hitActor, UPrimitiveComponent *hitComponent, FVector normalImpulse, const FHitResult &hit);

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class UParticleSystem *hitParticleSystem;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	class UParticleSystemComponent *particleSystemComponent;

	UPROPERTY(EditAnywhere, Category="Projectile")
	class USoundBase* hitSound;

	UPROPERTY(EditAnywhere, Category="Projectile")
	USoundBase* throwSound;

	UPROPERTY(EditAnywhere, Category= "Projectile")
	TSubclassOf<class UCameraShakeBase> hitCameraShakeClass;
};
