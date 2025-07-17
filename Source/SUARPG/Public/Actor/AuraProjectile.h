// Steven Oliveira

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class USoundBase;
class UAudioComponent;

UCLASS()
class SUARPG_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AAuraProjectile();

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Projectile")
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	

protected:

	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TObjectPtr<UAudioComponent> LoopingSoundComponent;

	bool bHit = false;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float LifeSpan = 15.f;

};
