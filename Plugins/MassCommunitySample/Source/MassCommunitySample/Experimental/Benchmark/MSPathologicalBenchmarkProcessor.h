﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "MSPathologicalBenchmarkProcessor.generated.h"

/*
 *
 *This is an ECS benchmark called Pathological invented by vblanco
 *It creates entities with a random sets of components as a stress test.
 *We start with 10 different components and create combinations of each from length 1 to 10.
 *Then we creates a massive list of 1023 different archetypes
 *This one of the worst performance cases for archetype style ECS implementations
 */
USTRUCT()
struct FAlberta : public FMassFragment
{
	GENERATED_BODY()
	int64 stuff;
};

USTRUCT()
struct FBritishColumbia : public FMassFragment
{
	GENERATED_BODY()
	int64 stuff;
};

USTRUCT()
struct FManitoba : public FMassFragment
{
	GENERATED_BODY()
	int64 stuff;
};

USTRUCT()
struct FNewBrunswick : public FMassFragment
{
	GENERATED_BODY()
	int64 stuff;
};

USTRUCT()
struct FNewfoundlandandLabrador : public FMassFragment
{
	GENERATED_BODY()
	int64 stuff;
};

USTRUCT()
struct FNovaScotia : public FMassFragment
{
	GENERATED_BODY()
	int64 stuff;
};

USTRUCT()
struct FOntario : public FMassFragment
{
	GENERATED_BODY()
	int64 stuff;
};

USTRUCT()
struct FPrinceEdwardIsland : public FMassFragment
{
	GENERATED_BODY()
	int64 stuff;
};

USTRUCT()
struct FQuebec : public FMassFragment
{
	GENERATED_BODY()
	int64 stuff;
};

USTRUCT()
struct FSaskatchewan : public FMassFragment
{
	GENERATED_BODY()
	int64 stuff;
};

USTRUCT()
struct FPathologicFragment : public FMassFragment
{
	GENERATED_BODY()
};

UCLASS()
class MASSCOMMUNITYSAMPLE_API UMSPathologicalBenchmarkProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:

	UMSPathologicalBenchmarkProcessor();

protected:

	TArray<UScriptStruct*> Combination;
	TArray<UScriptStruct*> Provinces;
	int NumCombinations;
	FMassEntityQuery PathologicQuery3;
	FMassEntityQuery PathologicQuery9;
	TArray<FMassArchetypeHandle> Archetypes;

public:

	void CombinationsRecursive(FMassEntityManager& EntityManager, int32 length, int32 offset);
	virtual void Initialize(UObject& Owner) override;

protected:

	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
};
