// Flynn's Rad Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
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
    
    UFUNCTION(BlueprintCallable, Category="Setup")
    void SpawnToStartLocation(float Speed);
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
    UStaticMeshComponent* PlayerMesh;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
    UBoxComponent* Box = nullptr;
    
    UPROPERTY(BlueprintReadOnly, Category="Setup")
    float Yaw = 0.f;
    
    UPROPERTY(BlueprintReadOnly, Category="Setup")
    FVector SpawnLocation;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
    float MovementSpeed = 2.f;
    
    UPROPERTY(BlueprintReadOnly, Category="Setup")
    float VerticalSpeed = 0.f;
    
    UPROPERTY(BlueprintReadOnly, Category="Setup")
    float HorizontalSpeed = 0.f;
    
private:
    void SetVerticalSpeed(float AxisValue);
    void SetHorizontalSpeed(float AxisValue);
    void UpdateShipHorizontalLocation();
    void UpdateShipVerticalLocation();
    
    float DeltaSeconds = 0.f;
    bool MoveEnabled = false;
    float CurrentSpeed = 0.f;
    float Health = 0.f;
    float MaxHealth = 0.f;
};
