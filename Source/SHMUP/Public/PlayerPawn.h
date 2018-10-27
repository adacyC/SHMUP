// Flynn's Rad Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SHMUP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

    virtual void Tick(float DeltaTime) override;
    
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
protected:
	virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
    UStaticMeshComponent* PlayerMesh;
    
    UPROPERTY(BlueprintReadOnly, Category="Setup")
    float Yaw = 0.f;
    
    UPROPERTY(BlueprintReadOnly, Category="Setup")
    FVector SpawnLocation;
    
private:
    bool MoveEnabled = false;
    float DeltaSeconds = 0.f;
    float HorizontalSpeed = 0.f;
    float VerticalSpeed = 0.f;
    float MovementSpeed = 0.f;
    float CurrentSpeed = 0.f;
    float Health = 0.f;
    float MaxHealth = 0.f;
};
