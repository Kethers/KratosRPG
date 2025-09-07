// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACTPickUpBase.generated.h"

class USphereComponent;

UCLASS()
class KRATOSRPG_API AACTPickUpBase : public AActor
{
	GENERATED_BODY()

public:
	AACTPickUpBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pick Up Interaction")
	USphereComponent* PickUpCollectionSphere;

	UFUNCTION()
	virtual void OnPickUpCollectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
