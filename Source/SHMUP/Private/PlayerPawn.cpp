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
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
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

