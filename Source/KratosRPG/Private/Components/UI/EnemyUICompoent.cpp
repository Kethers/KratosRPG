// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Components/UI/EnemyUICompoent.h"
#include "Widgets/ACTWidgetBase.h"

void UEnemyUICompoent::RegisterEnemyDrawnWidget(UACTWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUICompoent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty())
	{
		return;
	}

	for (UACTWidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}

	EnemyDrawnWidgets.Empty();
}
