﻿#pragma once
#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "Representation/MSNiagaraActor.h"
#include "MSRepresentationFragments.generated.h"

/**	Please keep in mind that we key NiagaraSystemFragments off of the pointer
*	to the niagara system selected in the trait.
*	Don't use the regular struct CRC32 hash like you would for other shared fragments.
**/
USTRUCT()
struct MASSCOMMUNITYSAMPLE_API FSharedNiagaraSystemFragment : public FMassSharedFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<AMSNiagaraActor> NiagaraManagerActor;

	//This is used to make sure we insert to the right space in the niagara array after iterating a chunk and so on
	int32 IteratorOffset = 0;


	inline static FName ParticlePositionsName = "MassParticlePositions";
	
	UPROPERTY()
	TArray<FVector> ParticlePositions;
	
	inline static FName ParticleOrientationsParameterName = "MassParticleOrientations";

	UPROPERTY()
	TArray<FQuat4f> ParticleOrientations;
	
	// todo: make this an instanced struct you can do whatever in?
	// This is quite gross but not having this here risks archetype sorting fun afaik
	
	// custom parameter data:
	inline static FName FirstCustomParticleDataName = "FirstCustomFloat";
	UPROPERTY()
	TArray<float> FirstCustomParticleData;
	inline static FName SecondCustomParticleDataName = "SecondCustomFloat";
	UPROPERTY()
	TArray<float> SecondCustomParticleData;

};
USTRUCT()
struct MASSCOMMUNITYSAMPLE_API FCustomNiagaraFloatsPairFragment : public FMassFragment
{
	GENERATED_BODY()
	float FirstFloat = 0.0f;
	float SecondFloat = 0.0f;
};


// This one is for responding to one-off events like a hit effect.
// I would argue it should be mapped based off of the physmat or something but oh well! 
USTRUCT()
struct MASSCOMMUNITYSAMPLE_API FSharedNiagaraSystemSpawnFragment : public FMassSharedFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<AMSNiagaraActor> NiagaraManagerActor;

	//This is used to make sure we insert to the right space in the niagara array after iterating a chunk and so on
	UPROPERTY()
	TArray<FVector> ParticlePositions;
	UPROPERTY(EditAnywhere)
	FName ParticlePositionsParameterName;

	
	UPROPERTY()
	TArray<FVector> ParticleDirectionVectors;
	
	UPROPERTY(EditAnywhere)
	FName ParticleDirectionVectorsParameterName;
	
	UPROPERTY(EditAnywhere)
	FName AuxParameterName;

};

USTRUCT()
struct MASSCOMMUNITYSAMPLE_API FSampleISMPerInstanceSingleFloatFragment : public FMassFragment
{
	GENERATED_BODY()
	float Data = 0.0f;
};



