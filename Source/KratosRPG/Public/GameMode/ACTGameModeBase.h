// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ACTTypes/ACTEnumTypes.h"
#include "ACTGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KRATOSRPG_API AACTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AACTGameModeBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
	EACTGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE EACTGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
};
