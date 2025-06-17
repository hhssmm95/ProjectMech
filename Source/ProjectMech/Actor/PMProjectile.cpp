// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PMProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/Damageable.h"
#include "UObject/Interface.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PMEffectPlayer.h"


//// Sets default values
//APMProjectile::APMProjectile()
//{
// 	
//}


APMProjectile::APMProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
    //CapsuleCollision->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
    SetRootComponent(CapsuleCollision);
    CapsuleCollision->InitCapsuleSize(5.0f, 2.0f);
    CapsuleCollision->SetCollisionProfileName(TEXT("Projectile"));

    // 안전한 TObjectPtr을 사용해 생성
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

    // 기본 속성 설정
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    ProjectileMesh->SetupAttachment(CapsuleCollision);

}

void APMProjectile::InitializeProjectileData(const FPMWeaponData& InWeaponData, FName TeamTag)
{
    WeaponData = InWeaponData;
    Tags.Add(TeamTag);
}

// Called when the game starts or when spawned
void APMProjectile::BeginPlay()
{
	Super::BeginPlay();

    SpawnTime = GetWorld()->GetTimeSeconds();


}

void APMProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &APMProjectile::OnDetectBeginOverlap);
}

// Called every frame
void APMProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - SpawnTime >= MaxLifeTime)
    {
        Destroy();  // 3초 경과 → 파괴

    }

}

void APMProjectile::OnDetectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (IsValid(this) && CheckOverlappedActorTags(OtherActor))
    {
        IDamageable* DamageableInterface = Cast<IDamageable>(OtherActor);
        TArray<AActor*> IgnoredActors;

        FVector ImpactPoint = SweepResult.ImpactPoint;
        FRotator HitEffectRotation = SweepResult.ImpactNormal.Rotation();
        //FVector ReverseForward = -GetActorForwardVector();
        //FRotator ReverseRotation = ReverseForward.Rotation();

        //FRotator HitEffectRotation = GetActorRotation();
        FActorSpawnParameters SpawnParams;
        //GL
        TArray<FHitResult> HitResults;
        FCollisionShape CollisionShape;
        FCollisionQueryParams QueryParams;
        bool bHit;
        TSet<AActor*> DamagedActors;

        if (HitEffectPlayerClass)
        {
            APMEffectPlayer* MuzzleFlashEffectPlayer = GetWorld()->SpawnActor<APMEffectPlayer>(HitEffectPlayerClass, ImpactPoint, HitEffectRotation, SpawnParams);
        }
        switch (WeaponData.WeaponType)
        {
        case EMechWeaponType::None:
            break;
        case EMechWeaponType::Gun:
            UGameplayStatics::ApplyDamage(OtherActor, WeaponData.Damage, GetInstigatorController(), this, UDamageType::StaticClass());
            break;
        case EMechWeaponType::GrenadeLauncher:
           /* UGameplayStatics::ApplyRadialDamage(GetWorld(), WeaponData.Damage, ImpactPoint, WeaponData.ExplosionRange/2,
                nullptr, IgnoredActors, this, GetInstigatorController(), true);*/
            

            // 구 형태의 충돌 체임 생성
            CollisionShape = FCollisionShape::MakeSphere(WeaponData.ExplosionRange);

            // 오버랩 시 자기 자신은 제외
            
            QueryParams.AddIgnoredActor(this);

            // Sphere Trace 수행 (시작과 끝이 동일하면 구 형태의 오버랩)
            bHit = GetWorld()->SweepMultiByChannel(
                HitResults,
                ImpactPoint,                   // 시작 위치
                ImpactPoint,                   // 끝 위치 (같은 지점)
                FQuat::Identity,          // 회전 없음
                ECC_GameTraceChannel5,                 // 충돌 채널 (필요에 따라 변경)
                CollisionShape,
                QueryParams
            );

            if (bHit)
            {
                for (const FHitResult& Hit : HitResults)
                {
                    AActor* HitActor = Hit.GetActor();

                    if (HitActor && !DamagedActors.Contains(HitActor))
                    {
                        // 데미지를 적용합니다.
                        UGameplayStatics::ApplyDamage(
                            HitActor,
                            WeaponData.Damage,
                            GetInstigatorController(),
                            this,
                            UDamageType::StaticClass()
                        );
                        // 이미 데미지를 준 액터 목록에 추가
                        DamagedActors.Add(HitActor);
                    }


                    //if (HitActor)
                    //{
                    //    // 예: 자신(self)은 제외하고, 필요한 추가 처리도 가능
                    //    UGameplayStatics::ApplyDamage(
                    //        HitActor,          // 데미지를 받을 액터
                    //        WeaponData.Damage,      // 데미지 값
                    //        GetInstigatorController(), // instigator controller. 상황에 맞게 조정
                    //        this,              // 데미지 causer
                    //        UDamageType::StaticClass() // 데미지 타입
                    //    );
                    //}
                }

                DrawDebugSphere(GetWorld(), ImpactPoint, WeaponData.ExplosionRange, 12, FColor::Green, false, 2.0f);
            }
            else
            {
                DrawDebugSphere(GetWorld(), ImpactPoint, WeaponData.ExplosionRange, 12, FColor::Red, false, 2.0f);
            }

            
            break;
        case EMechWeaponType::Laser:
            UGameplayStatics::ApplyDamage(OtherActor, WeaponData.Damage, GetInstigatorController(), this, UDamageType::StaticClass());
            break;
        case EMechWeaponType::Missile:
            UGameplayStatics::ApplyDamage(OtherActor, WeaponData.Damage, GetInstigatorController(), this, UDamageType::StaticClass());
            break;
        default:
            break;
        }
        //TODO: WeaponData를 총알에도 이관
        //UGameplayStatics::ApplyDamage(OtherActor, 1.f, )


        Destroy();
    }
}

bool APMProjectile::CheckOverlappedActorTags(const AActor* OtherActor)
{
    if (Tags.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile [%s] 's Tag is not initialized"), *GetName());
        return false;
    }

    if (OtherActor->Tags.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile[%s] Collision Target Actor [%s] 's Tag is not initialized"), *GetName(), *OtherActor->GetName());
        return false;
    }

    if (Tags[0] != OtherActor->Tags[0] || Tags[0] == FName("Prop"))
    {
        return true;
    }
    
    return false;
}

