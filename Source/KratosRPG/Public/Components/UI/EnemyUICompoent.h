// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "PawnUiComponent.h"
#include "EnemyUICompoent.generated.h"


class UACTWidgetBase;

UCLASS()
class KRATOSRPG_API UEnemyUICompoent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UACTWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:
	TArray<UACTWidgetBase*> EnemyDrawnWidgets;
};
