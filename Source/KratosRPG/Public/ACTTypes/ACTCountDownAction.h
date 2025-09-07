// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "ACTEnumTypes.h"

/**
 * 
 */
class FACTCountDownAction : public FPendingLatentAction
{
public:
	FACTCountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime,
		EACTCountDownActionOutput& InCountDownOutput, FLatentActionInfo& LatentInfo)
	: bNeedToCancel(false)
	, TotalCountDownTime(InTotalCountDownTime)
	, UpdateInterval(InUpdateInterval)
	, OutRemainingTime(InOutRemainingTime)
	, CountDownOutput(InCountDownOutput)
	, ExecutionFunction(LatentInfo.ExecutionFunction)
	, OutputLink(LatentInfo.Linkage)
	, CallbackTarget(LatentInfo.CallbackTarget)
	, ElapsedInterval(0.f)
	, ElapsedTimeSinceStart(0.f)
	{
		
	}

	virtual void UpdateOperation(FLatentResponse& Response) override;

	void CancelAction();

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EACTCountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};
