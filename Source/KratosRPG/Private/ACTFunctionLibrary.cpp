// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "ACTFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/ACTAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "ACTGameplayTags.h"
#include "ACTTypes/ACTCountDownAction.h"
#include "ACTGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/ACTSaveGame.h"

#include "ACTDebugHelper.h"

UACTAbilitySystemComponent* UACTFunctionLibrary::NativeGetActASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UACTAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UACTFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UACTAbilitySystemComponent* ASC = NativeGetActASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UACTFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UACTAbilitySystemComponent* ASC = NativeGetActASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UACTFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UACTAbilitySystemComponent* ASC = NativeGetActASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UACTFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EACTConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EACTConfirmType::Yes : EACTConfirmType::No;
}

UPawnCombatComponent* UACTFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UACTFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EACTValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EACTValidType::Valid : EACTValidType::Invalid;

	return CombatComponent;
}

bool UACTFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float UACTFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UACTFunctionLibrary::ComputeHitReactDirection(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return ACTGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return ACTGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference < -135.f || OutAngleDifference > 135.f)
	{
		return ACTGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return ACTGameplayTags::Shared_Status_HitReact_Right;
	}

	return ACTGameplayTags::Shared_Status_HitReact_Front;
}

bool UACTFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	// const FString DebugString = FString::Printf(TEXT("Dot Result: %f %s"), DotResult, DotResult < 0.f ? TEXT("Valid Block") : TEXT("Invalid Block"));
	//
	// Debug::Print(DebugString, DotResult < -0.1f ? FColor::Green : FColor::Red);

	return DotResult < -0.1f;
}

bool UACTFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UACTAbilitySystemComponent* SourceASC = NativeGetActASCFromActor(InInstigator);
	UACTAbilitySystemComponent* TargetASC = NativeGetActASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UACTFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime,
	EACTCountDownActionInput CountDownInput, UPARAM(DisplayName = "Output") EACTCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;

	if (GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}

	if (!World)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	FACTCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FACTCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (CountDownInput == EACTCountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FACTCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo)
			);
		}
	}

	if (CountDownInput == EACTCountDownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}

UACTGameInstance* UACTFunctionLibrary::GetACTGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UACTGameInstance>();
		}
	}

	return nullptr;
}

void UACTFunctionLibrary::ToggleInputMode(EACTInputMode InInputMode, const UObject* WorldContextObject)
{
	APlayerController* PlayerController = nullptr;

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}

	if (!PlayerController)
	{
		return;
	}

	FInputModeGameOnly GameOnlyMode;
	FInputModeUIOnly UIOnlyMode;

	switch (InInputMode)
	{
		case EACTInputMode::GameOnly:
			PlayerController->SetInputMode(GameOnlyMode);
			PlayerController->SetShowMouseCursor(false);
			break;

		case EACTInputMode::UIOnly:
			PlayerController->SetInputMode(UIOnlyMode);
			PlayerController->SetShowMouseCursor(true);
			break;
			
		default: ;
	}
}

void UACTFunctionLibrary::SaveCurrentGameDifficulty(EACTGameDifficulty InDifficultyToSave)
{
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(UACTSaveGame::StaticClass());

	if (UACTSaveGame* ACTSavedGameObject = Cast<UACTSaveGame>(SaveGameObject))
	{
		ACTSavedGameObject->SavedCurrentGameDifficulty = InDifficultyToSave;

		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(ACTSavedGameObject, ACTGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);

		Debug::Print(bWasSaved ? TEXT("Difficulty Saved") : TEXT("Difficulty NOT Saved"));
	}
}

bool UACTFunctionLibrary::TryLoadSavedGameDifficulty(EACTGameDifficulty& OutSavedDifficulty)
{
	if (UGameplayStatics::DoesSaveGameExist(ACTGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(ACTGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);

		if (UACTSaveGame* ACTSavedGameObject = Cast<UACTSaveGame>(SaveGameObject))
		{
			OutSavedDifficulty = ACTSavedGameObject->SavedCurrentGameDifficulty;

			Debug::Print(TEXT("Loading Successful"), FColor::Green);

			return true;
		}
	}

	return false;
}
