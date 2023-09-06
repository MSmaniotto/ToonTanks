// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Projectile.h"
#include "Components\CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule collider"));
	RootComponent = capsule;
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(capsule);
	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);
	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectileSpawnPoint->SetupAttachment(turretMesh);
}

void ABasePawn::HandleDestruction()
{
	// handle sound/other effects
	if (!!deathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			deathParticles,
			baseMesh->GetComponentLocation(),
			baseMesh->GetComponentRotation());
	}
	if (deathSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			this,
			deathSound,
			baseMesh->GetComponentLocation());
	}
	if (deathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(deathCameraShakeClass);
	}
}

void ABasePawn::RotateTurret(FVector targetPoint)
{
	FVector direction = targetPoint - turretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0, direction.Rotation().Yaw, 0);
	turretMesh->SetWorldRotation(
		FMath::RInterpTo(
			turretMesh->GetComponentRotation(),
			lookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			25.f),

		true);
}

void ABasePawn::fire()
{
	// DrawDebugSphere(
	//     GetWorld(),
	//     projectileSpawnPoint->GetComponentLocation(),
	//     30.f,
	//     12,
	//     FColor::Red,
	//     false,
	//     3.0f);

	AProjectile* createdProjectile = GetWorld()->SpawnActor<AProjectile>(projectile, projectileSpawnPoint->GetComponentLocation(), projectileSpawnPoint->GetComponentRotation());
	createdProjectile->SetOwner(this);
}
