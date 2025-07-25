﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	
	if (PlayerController)
		EndGame(false);

	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
			return;
	}
	
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// First way of doing things:
		// bool bIsPlayerController = Controller->IsPlayerController();
		// if (bIsPlayerWinner)
		// {
		// 	Controller->GameHasEnded(nullptr, bIsPlayerController);
		// }
		// else
		// {
		// 	Controller->GameHasEnded(nullptr, !bIsPlayerController);
		// }

		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
