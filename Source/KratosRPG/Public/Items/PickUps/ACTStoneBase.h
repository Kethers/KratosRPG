// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "ACTPickUpBase.h"
#include "ACTStoneBase.generated.h"

class UGameplayEffect;
class UACTAbilitySystemComponent;

UCLASS()
class KRATOSRPG_API AACTStoneBase : public AACTPickUpBase
{
	GENERATED_BODY()

public:
	void Consume(UACTAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);

protected:
	virtual void OnPickUpCollectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Stone Consumed"))
	void BP_OnStoneConsumed();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};
