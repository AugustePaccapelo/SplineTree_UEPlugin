// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineTreeComponent.h"

// ---------- STRUCTS ---------- \\

// ----- FSplineTreeJunctionInfos ----- \\

FSplineTreeJunctionInfos::FSplineTreeJunctionInfos(USplineTreeComponent* OtherSpline, int32 OtherIndex, int32 Prio)
{
	SplineConnected = OtherSpline;
	SplineIndex = OtherIndex;
	Priority = Prio;
}

// ---------- CLASS ---------- \\

// ----- USplineTreeComponent ----- \\

USplineTreeComponent::USplineTreeComponent()
{
	
}

void USplineTreeComponent::AddJonction_Implementation(USplineTreeComponent* OtherSpline, int32 OtherIndex, int32 ThisIndex, int32 Priority)
{
	if (!OtherSpline)
	{
		return;
	}
	
	if (!Junctions.Contains(ThisIndex))
	{
		Junctions.Add(ThisIndex, {});
	}
	
	Junctions[ThisIndex].SplineTreeJunctions.Add({ OtherSpline, OtherIndex, Priority });
	OtherSpline->SetLocationAtSplinePoint(
		OtherIndex,
		GetLocationAtSplinePoint(ThisIndex, ESplineCoordinateSpace::World),
		ESplineCoordinateSpace::World
	);
	OtherSpline->SetTangentsAtSplinePoint(
		OtherIndex,
		GetArriveTangentAtSplinePoint(ThisIndex, ESplineCoordinateSpace::World),
		GetLeaveTangentAtSplinePoint(ThisIndex, ESplineCoordinateSpace::World),
		ESplineCoordinateSpace::World
	);
}