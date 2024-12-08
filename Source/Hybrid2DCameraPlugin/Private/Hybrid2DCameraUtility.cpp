#include "Hybrid2DCameraUtility.h"

float FHybrid2DCameraUtility::GetFloatValueWithinRange(const float CurrentValue, const float TargetValue,
	const float MinValue, const float MaxValue)
{
	if (TargetValue < CurrentValue - MinValue || TargetValue > CurrentValue + MaxValue)
		return TargetValue;
	return CurrentValue;
}
