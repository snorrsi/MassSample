﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MSProjectileSimTrait.h"

#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "MassMovementFragments.h"
#include "Common/Fragments/MSFragments.h"

void UMSProjectileSimTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment<FMSCollisionIgnoredActorsFragment>();
	BuildContext.RequireFragment<FTransformFragment>();
	BuildContext.RequireFragment<FMassVelocityFragment>();
	BuildContext.AddTag<FMSProjectileTag>();
	BuildContext.AddTag<FMSLineTraceTag>();

	BuildContext.AddFragment(FConstStructView::Make(CollisionChannelFragment));

	

	if (bFiresHitEventToActors)
	{
		BuildContext.AddTag<FMSProjectileFireHitEventTag>();
	}
	if (bRicochet)
	{
		BuildContext.AddTag<FMSProjectileRicochetTag>();
	}
	if(bHasGravity)
	{
		BuildContext.AddTag<FMSGravityTag>();
	}
	if(bQueriesOctree)
	{
		BuildContext.AddTag<FMSOctreeQueryTag>();
	}

	if(bRotationFollowsVelocity)
	{
		BuildContext.AddTag<FMSRotationFollowsVelocityTag>();
	}
}
