#include "EngineMinimal.h"
#include "PoissonDisc.h"

PoissonDisc::PoissonDisc(uint32 Seed, float Width, float Height, float Depth)
{
	R = FRandomStream(Seed);
	Dimensions = FVector(Width, Height, Depth);
}

PoissonDisc::PoissonDisc(uint32 Seed, FVector Dimensions)
{
	R = FRandomStream(Seed);
	this->Dimensions = Dimensions;
}

void PoissonDisc::SetNumCandidates(uint32 N)
{
	NumCandidates = N;
}

// ****************************************************************************
// Next
//
// Selects a point within the bounds using Mitchells Best Candidate algorithm:
// 1. Randomly create N candidates within bounds
// 2. Select the candidate that is the furthest from all pre-existing points.
// ****************************************************************************
FVector PoissonDisc::Next()
{
	TArray<FVector> Candidates;

	for (uint32 i = 0; i < NumCandidates; i++)
	{
		Candidates.Add(FVector(R.FRandRange(0, Dimensions.X),
			R.FRandRange(0, Dimensions.Y), R.FRandRange(0, Dimensions.Z)));
	}

	FVector FurthestCandidate;
	float FurthestCandidateNNDistance = FLT_MIN;

	for (FVector& C : Candidates)
	{
		float CandidateNNDistance = FLT_MAX;

		for (FVector& P : Points)
		{
			float Distance = FVector::Dist(P, C);
			if (Distance < CandidateNNDistance)
			{
				CandidateNNDistance = Distance;
			}
		}

		if (CandidateNNDistance > FurthestCandidateNNDistance)
		{
			FurthestCandidate = C;
			FurthestCandidateNNDistance = CandidateNNDistance;
		}
	}

	Points.Add(FurthestCandidate);
	return FurthestCandidate;
}