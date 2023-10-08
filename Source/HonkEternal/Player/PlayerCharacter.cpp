// Made dy Titled Goose Team

#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/PlayerArmorComponent.h"
#include "Components/PlayerDamageManagerComponent.h"
#include "HonkEternal/Components/HealthComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	CameraComponent->bUsePawnControlRotation = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	ArmorComponent = CreateDefaultSubobject<UPlayerArmorComponent>("ArmorComponent");
	DamageManagerComponent = CreateDefaultSubobject<UPlayerDamageManagerComponent>("DamageManager");
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Aim
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Aim);

		//Shoot
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Shoot);

		//Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);

		//Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerCharacter::Dash);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);

		//Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APlayerCharacter::Pause);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (!IsAlive())
	{
		return; 
	}
	
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Aim(const FInputActionValue& Value)
{
	if (!IsAlive())
	{
		return; 
	}
	
	const FVector2D AimVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(AimVector.X);
		AddControllerPitchInput(AimVector.Y);
	}
}

void APlayerCharacter::Shoot()
{
	if (!IsAlive())
	{
		return; 
	}
	
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, "NYI. Player Shoot");
}

void APlayerCharacter::Dash()
{
	if (!IsAlive())
	{
		return; 
	}
	
	GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, "NYI. Player Dash");
}

void APlayerCharacter::Interact()
{
	if (!IsAlive())
	{
		return; 
	}
	
	GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Red, "NYI. Player Interaction");
}

void APlayerCharacter::Pause()
{
	if (!IsAlive())
	{
		return; 
	}
	
	GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Red, "NYI. Game Pause");
}
