// Flynn's Rad Copyright

#include "PlayerPawn.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
    
    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    RootComponent = Box;
    PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
    PlayerMesh->SetupAttachment(RootComponent);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
    Yaw = GetActorRotation().Yaw;
    SpawnLocation = GetActorLocation();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DeltaSeconds = DeltaTime;
    
    UpdateShipHorizontalLocation();
    UpdateShipVerticalLocation();
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    InputComponent->BindAxis("MoveUp", this, &APlayerPawn::SetVerticalSpeed);
    InputComponent->BindAxis("MoveRight", this, &APlayerPawn::SetHorizontalSpeed);
}

void APlayerPawn::SpawnToStartLocation(float Speed)
{
    FVector SpawnMoveAmount {0.f, 0.f, 60.f};
    FVector NewLocation = FMath::Lerp(SpawnLocation, (SpawnLocation + SpawnMoveAmount), Speed);
    SetActorLocation(NewLocation, true);
    
    float SpawnSpinDegrees = 1440.f;
    FRotator SpinRotation {0.f, 0.f, (Yaw + SpawnSpinDegrees)};
    FRotator FinalRotation = FMath::Lerp({0.f, 0.f, 0.f}, SpinRotation, Speed);
    PlayerMesh->SetRelativeRotation(FinalRotation);
}

void APlayerPawn::SetVerticalSpeed(float AxisValue)
{
    VerticalSpeed = FMath::FInterpTo(VerticalSpeed, (MovementSpeed * AxisValue), DeltaSeconds, 6);
}

void APlayerPawn::SetHorizontalSpeed(float AxisValue)
{
    HorizontalSpeed = FMath::FInterpTo(HorizontalSpeed, (MovementSpeed * AxisValue), DeltaSeconds, 6);
}

void APlayerPawn::UpdateShipHorizontalLocation()
{
    FVector ShipLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    
    FVector HorizontalLocationModifier {HorizontalSpeed, 0.f, 0.f};
    FVector NewHorizontalLocation = ShipLocation + HorizontalLocationModifier;
    SetActorLocation(NewHorizontalLocation, true);
    
    float HorizontalSpeedModifier = -7.f;
    float InterpolationSpeed = 80.f;
    FRotator TargetRotation {0.f, HorizontalSpeed * HorizontalSpeedModifier + Yaw, 0.f};
    PlayerMesh->SetRelativeRotation(FMath::RInterpConstantTo(PlayerMesh->GetRelativeTransform().GetRotation().Rotator(), TargetRotation, DeltaSeconds, InterpolationSpeed), true);
}

void APlayerPawn::UpdateShipVerticalLocation()
{
    FVector ShipLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    
    FVector VerticalLocationModifier {0.f, 0.f, VerticalSpeed};
    FVector NewVerticalLocation = ShipLocation + VerticalLocationModifier;
    SetActorLocation(NewVerticalLocation, true);
}
