
#pragma once


class PoissonDisc
{
public:
	PoissonDisc(uint32 Seed, FVector Dimensions);
	PoissonDisc(uint32 Seed, float Width, float Height, float Depth);
	~PoissonDisc() {}

	void SetNumCandidates(uint32 N);
	FVector Next();

private:
	uint32 NumCandidates;
	FRandomStream R;
	FVector Dimensions;
	TArray<FVector> Points;
};