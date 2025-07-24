// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot Player");
}


EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ShooterAIController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	if (!ShooterAIController)
		return EBTNodeResult::Failed;
	
	Character = Cast<AShooterCharacter>(ShooterAIController->GetPawn());
	if (!Character)
		return EBTNodeResult::Failed;
	
	Character->DoShoot();

	return EBTNodeResult::Succeeded;
}
