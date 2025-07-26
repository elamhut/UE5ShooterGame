// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
class USpringArmComponent;

UCLASS()
class SHOOTERASSETPACK_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DoMove(const FVector2D& MovementVector);
	void DoLook(const FVector2D& LookVector);
	void DoJump();
	void DoShoot();

	UFUNCTION(BlueprintPure)
	bool IsDead() const { return Health <= 0; }

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const { return Health / MaxHealth; };

	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere)
	float MovementSpeed{100.f};

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth{100.f};

	UPROPERTY(VisibleAnywhere)
	float Health{0};

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	TObjectPtr<AGun> Gun;
};
