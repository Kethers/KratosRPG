// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/ACTCharacterAnimInstance.h"
#include "ACTHeroAnimInstance.generated.h"

class AACTHeroCharacter;
/**
 * 
 */
UCLASS()
class KRATOSRPG_API UACTHeroAnimInstance : public UACTCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "AnimData|References")
	AACTHeroCharacter* OwningHeroCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;

	float IdleElapsedTime;
};
