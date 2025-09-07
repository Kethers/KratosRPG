// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Widgets/ACTWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"

void UACTWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
		{
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
		}
	}
}

void UACTWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		if (UEnemyUICompoent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent())
		{
			checkf(EnemyUIComponent, TEXT("Failed to extract an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel())

			BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
		}
	}
}
