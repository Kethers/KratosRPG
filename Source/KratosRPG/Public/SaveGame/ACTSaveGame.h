// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ACTTypes/ACTEnumTypes.h"
#include "ACTSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class KRATOSRPG_API UACTSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	EACTGameDifficulty SavedCurrentGameDifficulty;
};
