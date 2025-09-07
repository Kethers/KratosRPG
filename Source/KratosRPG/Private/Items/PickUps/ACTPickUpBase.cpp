// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Items/PickUps/ACTPickUpBase.h"
#include "Components/SphereComponent.h"


// Sets default values
AACTPickUpBase::AACTPickUpBase()
{
	PrimaryActorTick.bCanEverTick = false;

	PickUpCollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollectionSphere"));
	SetRootComponent(PickUpCollectionSphere);
	PickUpCollectionSphere->InitSphereRadius(50.f);
	PickUpCollectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPickUpCollectionSphereBeginOverlap);
}

void AACTPickUpBase::OnPickUpCollectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
