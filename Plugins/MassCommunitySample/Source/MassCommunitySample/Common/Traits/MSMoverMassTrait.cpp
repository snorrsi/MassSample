﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MSMoverMassTrait.h"

#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "MassMovementFragments.h"
#include "Common/Fragments/MSFragments.h"

void UMSMoverMassTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.RequireFragment<FTransformFragment>();
	BuildContext.RequireFragment<FMassVelocityFragment>();
	BuildContext.AddFragment_GetRef<FMassForceFragment>().Value = StartingForce;

	BuildContext.AddTag<FMSBasicMovement>();

}
