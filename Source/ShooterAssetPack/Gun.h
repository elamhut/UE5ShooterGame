﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERASSETPACK_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

	virtual void Tick(float DeltaTime) override;
	AController* GetOwnerController() const;
	void PullTrigger();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> RootSceneComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> GunMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> MuzzleFlash;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> MuzzleSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
	float MaxRange{1000.f};

	UPROPERTY(EditAnywhere)
	float Damage;
};
