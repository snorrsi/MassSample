// Fill out your copyright notice in the Description page of Project Settings.


#include "MSProjectileSimProcessors.h"

#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassCommonUtils.h"
#include "MassExecutionContext.h"
#include "MassMovementFragments.h"
#include "MassSignalSubsystem.h"
#include "Common/Fragments/MSFragments.h"
#include "Experimental/Physics/MSMassCollision.h"
#include "ProjectileSim/Fragments/MSProjectileFragments.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MSProjectileSimProcessors)


void UMSProjectileSimProcessors::InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& Manager)
{
	Super::InitializeInternal(Owner, Manager);
}


UMSProjectileSimProcessors::UMSProjectileSimProcessors()
{
	ExecutionOrder.ExecuteAfter.Add(UE::Mass::ProcessorGroupNames::Movement);

	ExecutionFlags = (int32)(EProcessorExecutionFlags::All);
}

void UMSProjectileSimProcessors::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	LineTraceFromPreviousPosition.Initialize(EntityManager);
	LineTraceFromPreviousPosition.AddRequirement<FMSCollisionIgnoredActorsFragment>(EMassFragmentAccess::ReadWrite, EMassFragmentPresence::Optional);

	LineTraceFromPreviousPosition.AddRequirement<FMassVelocityFragment>(EMassFragmentAccess::ReadOnly);
	LineTraceFromPreviousPosition.AddRequirement<FMSCollisionChannelFragment>(EMassFragmentAccess::ReadOnly);
	LineTraceFromPreviousPosition.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
	LineTraceFromPreviousPosition.AddTagRequirement<FMSProjectileTag>(EMassFragmentPresence::All);
	LineTraceFromPreviousPosition.AddTagRequirement<FMSLineTraceTag>(EMassFragmentPresence::All);

	LineTraceFromPreviousPosition.RegisterWithProcessor(*this);

	ProcessorRequirements.AddSubsystemRequirement<UMassSignalSubsystem>(EMassFragmentAccess::ReadWrite);
}

void UMSProjectileSimProcessors::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	TQueue<FMassEntityHandle, EQueueMode::Mpsc> EntitiesThatHitSomething;
	std::atomic<int32> NumEntitiesThatHitSomething;
	
	LineTraceFromPreviousPosition.ForEachEntityChunk( Context, [&](FMassExecutionContext& Context)
	{
		QUICK_SCOPE_CYCLE_COUNTER(STAT_MASS_LineTraceFromPreviousPosition);


		const TArrayView<FMSCollisionIgnoredActorsFragment> IgnoredActorsFragments = Context.GetMutableFragmentView<
			FMSCollisionIgnoredActorsFragment>();
		TConstArrayView<FMassVelocityFragment> Velocities = Context.GetFragmentView<FMassVelocityFragment>();
		TConstArrayView<FTransformFragment> Transforms = Context.GetFragmentView<FTransformFragment>();
		TConstArrayView<FMSCollisionChannelFragment> CollisionChannels = Context.GetFragmentView<FMSCollisionChannelFragment>();

		int32 NumEntities = Context.GetNumEntities();

		FCollisionQueryParams QueryParams;
		for (int32 i = 0; i < NumEntities; ++i)

		{
			FHitResult HitResult;

			FVector CurrentLocation = Transforms[i].GetTransform().GetTranslation();
			FVector Velocity = Velocities[i].Value;

			TEnumAsByte<ECollisionChannel> CollisionChannel = CollisionChannels[i].Channel;


			QueryParams.ClearIgnoredActors();

			//todo-perf: somehow keep the query params around as this is fairly evil to do
			if (IgnoredActorsFragments.Num() > 0)
			{
				for (const AActor* IgnoredActor : IgnoredActorsFragments[i].IgnoredActors) {
					QueryParams.AddIgnoredActor(IgnoredActor);
				}
			}


			if (GetWorld()->LineTraceSingleByChannel(HitResult,
			                                         // Create the previous location from our velocity
			                                         CurrentLocation - (Velocity * Context.GetDeltaTimeSeconds()), CurrentLocation, CollisionChannel,
			                                         QueryParams))
			{
				FMassEntityHandle Entity = Context.GetEntity(i);

				EntitiesThatHitSomething.Enqueue(Entity);
				++NumEntitiesThatHitSomething;
				Context.Defer().PushCommand<FMassCommandAddFragmentInstances>(Entity, FMSHitResultFragment(HitResult));
			}
		}
	});


	if (NumEntitiesThatHitSomething > 0)
	{
		TArray<FMassEntityHandle> Entities = UE::Mass::Utils::EntityQueueToArray(EntitiesThatHitSomething, NumEntitiesThatHitSomething);

		Context.GetMutableSubsystem<UMassSignalSubsystem>()->SignalEntities(MassSample::Signals::OnEntityHitSomething, Entities);
	}
}
