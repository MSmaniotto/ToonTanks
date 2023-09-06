// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Tank.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

/*ATurret::ATurret(){
    PrimaryActorTick.bCanEverTick= true;
}*/

void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(CheckFireCondition()){
        RotateTurret(tank->GetActorLocation());
    }
}

void ATurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATurret::BeginPlay()
{
    Super::BeginPlay();
    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(timerHandle, this, &ATurret::triggerFire, fireRate, true);
}

void ATurret::triggerFire(){
    if(CheckFireCondition()){
        fire();
    }
}

bool ATurret::CheckFireCondition()
{
    if(tank && !!tank->bAlive){
        float distance = FVector::Distance(GetActorLocation(), tank->GetActorLocation());
        if (distance <= range)
        {
            return true;
        }
    }
    return false;
}
