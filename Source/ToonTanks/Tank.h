// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	
	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:
		ATank();
		APlayerController* GetPlayerControllerRef() const;
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

		void HandleDestruction() override;

		bool bAlive = true;
	private:
		void Move(float value);
        void Turn(float value);
		APlayerController* playerControllerRef;
        UPROPERTY(EditAnywhere, Category = "Movement")
        float speed=200.f;
		UPROPERTY(EditAnywhere, Category = "Movement")
        float turnRate=60.f;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
		class USpringArmComponent* springArm;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
		class UCameraComponent* camera;
	
};
