// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "ShooterCharacter.h"

AShooterPlayerController::AShooterPlayerController()
{
	InputMappingContext = CreateDefaultSubobject<UInputMappingContext>("Input Mapping");
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	checkf(LocalPlayer, TEXT("No LocalPlayer Found, unfortunately."))

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	checkf(Subsystem, TEXT("No Enhanced Input Subsystem found, unfortunately!"))
	Subsystem->AddMappingContext(InputMappingContext, 0);

	PlayerPawn = Cast<AShooterCharacter>(GetPawn());
	checkf(PlayerPawn, TEXT("No LocalPlayer Found, unfortunately."))

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Couldn't Get Enhanced Input Component!"))

	EnhancedInputComponent->BindAction(MoveAction,
	                                   ETriggerEvent::Triggered,
	                                   this,
	                                   &AShooterPlayerController::HandleMove);

	EnhancedInputComponent->BindAction(LookAction,
	                                   ETriggerEvent::Triggered,
	                                   this,
	                                   &AShooterPlayerController::HandleLook);

	EnhancedInputComponent->BindAction(JumpAction,
	                                   ETriggerEvent::Started,
	                                   this,
	                                   &AShooterPlayerController::HandleJump);
}

void AShooterPlayerController::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementValues = InputActionValue.Get<FVector2D>();
	PlayerPawn->DoMove(MovementValues);
}

void AShooterPlayerController::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();
	PlayerPawn->DoLook(LookVector);
}

void AShooterPlayerController::HandleJump()
{
	PlayerPawn->DoJump();
}
