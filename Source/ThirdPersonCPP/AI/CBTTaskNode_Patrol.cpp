#include "CBTTaskNode_Patrol.h"
#include "Global.h"
#include "AIController.h"
#include "Components/CActionComponent.h"
#include "Components/CPatrolComponent.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
    NodeName = "Patrol";
    
    bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    //순찰 경로 유무
    AAIController* AIC = Cast<AAIController>(OwnerComp.GetOwner());
    CheckNullResult(AIC, EBTNodeResult::Failed);

    APawn* Pawn = AIC->GetPawn();
    CheckNullResult(Pawn, EBTNodeResult::Failed);

    UCPatrolComponent* PatrolComp = CHelpers::GetComponent<UCPatrolComponent>(Pawn);

    if (PatrolComp->IsPathValid() == false)
    {
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    //실제 이동
    AAIController* AIC = Cast<AAIController>(OwnerComp.GetOwner());
    CheckNull(AIC);

    APawn* Pawn = AIC->GetPawn();
    CheckNull(Pawn);

    UCPatrolComponent* PatrolComp = CHelpers::GetComponent<UCPatrolComponent>(Pawn);

    FVector Location;
    PatrolComp->GetMoveTo(Location);

    AIC->MoveToLocation(Location);

    EPathFollowingRequestResult::Type RequestResult = AIC->MoveToLocation(Location);

    if (RequestResult == EPathFollowingRequestResult::Failed)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }
    else if (RequestResult == EPathFollowingRequestResult::AlreadyAtGoal)
    {
        PatrolComp->UpdateNextIndex();

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
