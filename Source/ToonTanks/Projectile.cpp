// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = baseMesh;
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement"));
	projectileMovement->InitialSpeed = 50.f;
	projectileMovement->MaxSpeed = 70.f;

	particleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile trail"));
	particleSystemComponent->SetupAttachment(baseMesh);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	baseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (throwSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			this,
			throwSound,
			baseMesh->GetComponentLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent *smasherComp, AActor *hitActor, UPrimitiveComponent *hitComponent, FVector normalImpulse, const FHitResult &hit)
{
	AActor* myOwner = GetOwner();
	UClass* damageType = UDamageType::StaticClass();

	if (!myOwner)
	{
		Destroy();
		return;
	}

	if (hitActor && hitActor != this && hitActor != myOwner)
	{
		UGameplayStatics::ApplyDamage(
			hitActor,
			damage,
			myOwner->GetInstigatorController(),
			smasherComp->GetOwner(),
			damageType);
		if (!!hitParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				this,
				hitParticleSystem,
				baseMesh->GetComponentLocation(),
				baseMesh->GetComponentRotation());
		}
	}
	if (hitSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			this,
			hitSound,
			baseMesh->GetComponentLocation());
	}
	if (hitCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShakeClass);
	}
	Destroy();
}
