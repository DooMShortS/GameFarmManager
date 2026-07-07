// Copyright Epic Games, Inc. All Rights Reserved.

#include "FarmWorldGeneratorSubsystem.h"
#include "FarmWorldProfile.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Box2D.h"

UFarmWorldProfile* UFarmWorldGeneratorSubsystem::CreateNewProfile()
{
	WorkingProfile = Cast<UFarmWorldProfile>(UGameplayStatics::CreateSaveGameObject(UFarmWorldProfile::StaticClass()));
	return WorkingProfile;
}

bool UFarmWorldGeneratorSubsystem::IsPointInsidePerimeter(const FVector2D& Point, const TArray<FVector2D>& PerimeterPoints)
{
	const int32 NumPoints = PerimeterPoints.Num();
	if (NumPoints < 3)
	{
		return false;
	}

	// standard ray-casting point-in-polygon test
	bool bInside = false;
	for (int32 Index = 0, PrevIndex = NumPoints - 1; Index < NumPoints; PrevIndex = Index++)
	{
		const FVector2D& A = PerimeterPoints[Index];
		const FVector2D& B = PerimeterPoints[PrevIndex];

		const bool bCrosses = ((A.Y > Point.Y) != (B.Y > Point.Y)) &&
			(Point.X < (B.X - A.X) * (Point.Y - A.Y) / (B.Y - A.Y) + A.X);

		if (bCrosses)
		{
			bInside = !bInside;
		}
	}

	return bInside;
}

float UFarmWorldGeneratorSubsystem::GetPerimeterArea(const TArray<FVector2D>& PerimeterPoints)
{
	const int32 NumPoints = PerimeterPoints.Num();
	if (NumPoints < 3)
	{
		return 0.0f;
	}

	// shoelace formula
	float Area = 0.0f;
	for (int32 Index = 0, PrevIndex = NumPoints - 1; Index < NumPoints; PrevIndex = Index++)
	{
		const FVector2D& A = PerimeterPoints[PrevIndex];
		const FVector2D& B = PerimeterPoints[Index];
		Area += A.X * B.Y - B.X * A.Y;
	}

	return FMath::Abs(Area) * 0.5f;
}

bool UFarmWorldGeneratorSubsystem::ValidateFarmhousePlacement() const
{
	if (!WorkingProfile)
	{
		return false;
	}

	const FVector2D FarmhouseLocation2D(WorkingProfile->FarmhouseTransform.GetLocation());
	return IsPointInsidePerimeter(FarmhouseLocation2D, WorkingProfile->PerimeterPoints);
}

TArray<FVector2D> UFarmWorldGeneratorSubsystem::GenerateScatterPoints(int32 Count, int32 ScatterChannel) const
{
	TArray<FVector2D> Points;

	if (!WorkingProfile || WorkingProfile->PerimeterPoints.Num() < 3 || Count <= 0)
	{
		return Points;
	}

	const TArray<FVector2D>& Perimeter = WorkingProfile->PerimeterPoints;

	FBox2D Bounds(ForceInit);
	for (const FVector2D& Point : Perimeter)
	{
		Bounds += Point;
	}

	FRandomStream Stream(WorkingProfile->RandomSeed + ScatterChannel);

	constexpr int32 MaxAttemptsPerPoint = 50;
	Points.Reserve(Count);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		for (int32 Attempt = 0; Attempt < MaxAttemptsPerPoint; ++Attempt)
		{
			const FVector2D Candidate(
				Stream.FRandRange(Bounds.Min.X, Bounds.Max.X),
				Stream.FRandRange(Bounds.Min.Y, Bounds.Max.Y));

			if (IsPointInsidePerimeter(Candidate, Perimeter))
			{
				Points.Add(Candidate);
				break;
			}
		}
	}

	return Points;
}

bool UFarmWorldGeneratorSubsystem::SaveWorkingProfile(const FString& SlotName)
{
	if (!WorkingProfile)
	{
		return false;
	}

	return UGameplayStatics::SaveGameToSlot(WorkingProfile, SlotName, 0);
}
