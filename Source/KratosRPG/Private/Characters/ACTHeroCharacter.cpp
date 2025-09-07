// Kethers's learning-purpose project following Vince Petrelli's Warrior project tutorial from udemy


#include "Characters/ACTHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Input/ACTInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "ACTGameplayTags.h"
#include "AbilitySystem/ACTAbilitySystemComponent.h"
#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameMode/ACTGameModeBase.h"

#include "ACTDebugHelper.h"

AACTHeroCharacter::AACTHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
}

UPawnCombatComponent* AACTHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* AACTHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* AACTHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void AACTHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = 1;

			if (AACTGameModeBase* BaseGameMode = GetWorld()->GetAuthGameMode<AACTGameModeBase>())
			{
				switch (BaseGameMode->GetCurrentGameDifficulty())
				{
				case EACTGameDifficulty::Easy:
					AbilityApplyLevel = 4;
					Debug::Print(TEXT("Current Difficulty: Easy"));
					break;

				case EACTGameDifficulty::Normal:
					AbilityApplyLevel = 3;
					Debug::Print(TEXT("Current Difficulty: Normal"));
					break;

				case EACTGameDifficulty::Hard:
					AbilityApplyLevel = 2;
					Debug::Print(TEXT("Current Difficulty: Hard"));
					break;

				case EACTGameDifficulty::VeryHard:
					AbilityApplyLevel = 1;
					Debug::Print(TEXT("Current Difficulty: Very Hard"));
					break;

				default:
					break;
				}
			}

			LoadedData->GiveToAbilitySystemComponent(ACTAbilitySystemComponent, AbilityApplyLevel);
		}
	}
}

void AACTHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"))
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UACTInputComponent* ACTInputComponent = CastChecked<UACTInputComponent>(PlayerInputComponent);

	ACTInputComponent->BindNativeInputAction(InputConfigDataAsset, ACTGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	ACTInputComponent->BindNativeInputAction(InputConfigDataAsset, ACTGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	ACTInputComponent->BindNativeInputAction(InputConfigDataAsset, ACTGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	ACTInputComponent->BindNativeInputAction(InputConfigDataAsset, ACTGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	ACTInputComponent->BindNativeInputAction(InputConfigDataAsset, ACTGameplayTags::InputTag_PickUp_Stones, ETriggerEvent::Started, this, &ThisClass::Input_PickUpStonesStarted);

	ACTInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void AACTHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AACTHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotator.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotator.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AACTHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AACTHeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void AACTHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f ? ACTGameplayTags::Player_Event_SwitchTarget_Right : ACTGameplayTags::Player_Event_SwitchTarget_Left,
		Data
	);
}

void AACTHeroCharacter::Input_PickUpStonesStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		ACTGameplayTags::Player_Event_ConsumeStones,
		Data
	);
}

void AACTHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	ACTAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AACTHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	ACTAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
