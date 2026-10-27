// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "SplineTreeComponent.generated.h"

class USplineTreeComponent;


/**
 * Structure to keep variables of a junction of Spline Trees.
 * Keep a pointer to the other spline, it's index & a priority (0 Highest).
*/
USTRUCT(BlueprintType, Blueprintable)
struct FSplineTreeJunctionInfos
{
	GENERATED_BODY()
	
	// ---------- VARIABLES ---------- \\
	
	// ----- Objects ----- \\

public:
	/**
	 * Pointer to the connected spline.
	*/
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USplineTreeComponent> SplineConnected;
	
	// ----- Others ----- \\
	
	/**
	 * The point index of the connected spline. 
	*/
	UPROPERTY(BlueprintReadWrite)
	int32 SplineIndex;
	/**
	 * The junction priority, to choose wich spline is considered as the next child.
	 * 0 is the highest priority.
	*/
	UPROPERTY(BlueprintReadWrite)
	int32 Priority = 0;
};

/**
 * Just contain an array of FSplineTreeJunctionInfos so a map can have an array as value.
 */
USTRUCT(BlueprintType, Blueprintable)
struct FSplineTreeArray
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FSplineTreeJunctionInfos> SplineTreeJunctions;
};

/**
 * Spline component to allow interconnection between multiple splines of the same type
 */
UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class SPLINETREE_API USplineTreeComponent : public USplineComponent
{
	GENERATED_BODY()
	
	// ---------- VARIABLES ---------- \\
	
	// ----- Others ----- \\
	
protected:
	/**
	 * Map of junctions of this spline. 
	 * Key : Index of this spline point junction
	 * Value : All the spline connected at this point
	*/
	UPROPERTY(BlueprintReadWrite)
	TMap<int32, FSplineTreeArray> Junctions;
	
	// ---------- FUNCTIONS ---------- \\
	
	
};
