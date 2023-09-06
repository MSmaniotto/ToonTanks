// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerController(bool flag)
{
    if(flag== false && !!GetPawnOrSpectator()){
        GetPawnOrSpectator()->DisableInput(this);
    }
    if(flag==true && !!GetPawnOrSpectator()){
        GetPawnOrSpectator()->EnableInput(this);
    }
    bShowMouseCursor = flag;
}

void AToonTanksPlayerController::BeginPlay()
{
    Super::BeginPlay();
}