// Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

#include "AI/EQS/EnvQueryTest_PickupCouldBeTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/UA3BasePickup.h"

UEnvQueryTest_PickupCouldBeTaken::UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
    const auto DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    bool WantsBeTakable = BoolValue.GetValue();

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto PickupActor = Cast<AUA3BasePickup>(ItemActor);
        if (!PickupActor)
            continue;

        const auto CouldBeTaken = PickupActor->CouldBeTaken();
        It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakable);
    }
}
