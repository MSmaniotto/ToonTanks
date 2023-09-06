// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    springArm= CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    springArm->SetupAttachment(RootComponent);
    camera= CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera->SetupAttachment(springArm);
    
}

APlayerController *ATank::GetPlayerControllerRef() const
{
    return playerControllerRef;
}

void ATank::Move(float value)
{
    FVector vector= FVector(0.f);
    float deltaTime= UGameplayStatics::GetWorldDeltaSeconds(this);
    vector.X=value*deltaTime*speed;
    AddActorLocalOffset(vector,true);
}

void ATank::Turn(float value)
{
    float deltaTime= UGameplayStatics::GetWorldDeltaSeconds(this);
    FRotator deltaRotation(0.0, deltaTime*value*turnRate, 0.0);
    AddActorLocalRotation(deltaRotation, true);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::fire);
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    bAlive = false;
    Destroy();
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    playerControllerRef=Cast<APlayerController>(GetController());
    
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FHitResult hitResult;
    playerControllerRef->GetHitResultUnderCursor(
        ECollisionChannel::ECC_Visibility, 
        false,
        hitResult
    );
    
    //TODO REMOVE
    DrawDebugSphere(
        GetWorld(), 
        hitResult.ImpactPoint, 
        30.f, 
        12,
        FColor::Magenta,
        false,
        -1.0f);

    RotateTurret(hitResult.ImpactPoint);
}
