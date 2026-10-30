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

// ----- FSplineTreeArray ----- \\

bool FSplineTreeArray::DoesContainSpline(USplineTreeComponent* OtherSpline)
{
	for (FSplineTreeJunctionInfos Junction : SplineTreeJunctions)
	{
		if (Junction.SplineConnected == OtherSpline)
		{
			return true;
		}
	}
	
	return false;
}

// ---------- CLASS ---------- \\

// ----- USplineTreeComponent ----- \\

USplineTreeComponent::USplineTreeComponent()
{
	
}

void USplineTreeComponent::AddJonction_Implementation(USplineTreeComponent* OtherSpline, int32 OtherIndex, int32 ThisIndex, int32 ThisPriority, int32 OtherPriority)
{
	if (!OtherSpline)
	{
		return;
	}
	
	if (!Junctions.Contains(ThisIndex))
	{
		Junctions.Add(ThisIndex, {});
	}
	
	if (Junctions[ThisIndex].DoesContainSpline(OtherSpline))
	{
		return;
	}
	
	Junctions[ThisIndex].SplineTreeJunctions.Add({ OtherSpline, OtherIndex, OtherPriority });
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
	
	OtherSpline->AddJonction(
		this, ThisIndex, OtherIndex, ThisPriority, OtherPriority
		);
}