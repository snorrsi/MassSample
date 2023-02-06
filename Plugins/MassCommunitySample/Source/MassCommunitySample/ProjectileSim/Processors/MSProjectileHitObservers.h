﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassObserverProcessor.h"
#include "MassSignalProcessorBase.h"
#include "UObject/Object.h"
#include "MSProjectileHitObservers.generated.h"

/**
 * 
 */ 
UCLASS()
class MASSCOMMUNITYSAMPLE_API UMSProjectileHitObservers : public UMassObserverProcessor
{
	GENERATED_BODY()
public:
	UMSProjectileHitObservers();
	
protected:
	
	virtual void ConfigureQueries() override;
	
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery ResolveHitsQuery;
	FMassEntityQuery RicochetHitsQuery;

	FMassEntityQuery CollisionHitEventQuery;

};

UCLASS()
class MASSCOMMUNITYSAMPLE_API UMSEntityWasHitSignalProcessor : public UMassSignalProcessorBase
{
	GENERATED_BODY()
public:
	UMSEntityWasHitSignalProcessor();


	
	virtual void ConfigureQueries() override;
	

	virtual void Initialize(UObject& Owner) override;


	virtual void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& EntitySignals) override;
	FMassEntityQuery ResolveCollisionsQuery;

	

};