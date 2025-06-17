// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PMMechBase.h"
#include "Character/PMAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Component/PMHUDComponent.h"
#include "Component/PMStatComponent.h"
#include "Components/SphereComponent.h"
#include "Actor/PMMechWeapon.h"
#include "GameConstants.h"
#include "Game/PMGameInstance.h"
#include "Controller/PMAIController.h"
#include "Actor/PMEffectPlayer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APMMechBase::APMMechBase()
{
	PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    // Capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

    // Camera
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;


    // Movement
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // HUD Component
    HUDComponent = CreateDefaultSubobject<UPMHUDComponent>(TEXT("HUDComponent"));
    StatComponent = CreateDefaultSubobject<UPMStatComponent>(TEXT("StatComponent"));
    // Sphere Component
    DetectSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DetectSphereComponent"));
    DetectSphereComponent->SetupAttachment(RootComponent);
    DetectSphereComponent->SetSphereRadius(1000.f);
    DetectSphereComponent->SetCollisionProfileName(TEXT("DetectEnemy"));

    

    RightArmWeaponSlot = CreateDefaultSubobject <UChildActorComponent>(TEXT("RightArmWeaponSlot"));
    RightArmWeaponSlot->SetupAttachment(GetMesh());


    LeftArmWeaponSlot = CreateDefaultSubobject <UChildActorComponent>(TEXT("LeftArmWeaponSlot"));
    LeftArmWeaponSlot->SetupAttachment(GetMesh());


    RightShoulderWeaponSlot = CreateDefaultSubobject <UChildActorComponent>(TEXT("RightShoulderWeaponSlot"));
    RightShoulderWeaponSlot->SetupAttachment(GetMesh());


    LeftShoulderWeaponSlot = CreateDefaultSubobject <UChildActorComponent>(TEXT("LeftShoulderWeaponSlot"));
    LeftShoulderWeaponSlot->SetupAttachment(GetMesh());
}



float APMMechBase::ApplyDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    return 0.0f;
}

void APMMechBase::ApplyDeath()
{
    StatComponent->SetCurrentAP(0);
    Destroy();
}


void APMMechBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    HUDComponent->OnHUDInitialized.AddDynamic(this, &APMMechBase::HandleHUDInitialized);
    StatComponent->OnStatInitialized.AddDynamic(this, &APMMechBase::HandleStatInitialized);
    DetectSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APMMechBase::OnDetectBeginOverlap);
    DetectSphereComponent->OnComponentEndOverlap.AddDynamic(this, &APMMechBase::OnDetectEndOverlap);

    //if (HUDComponent = FindComponentByClass<UPMHUDComponent>()) 

}

void APMMechBase::BeginPlay()
{
    Super::BeginPlay();

    if (DefaultMappingContext == nullptr)
    {
        return;
    }

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
        bIsPlayerMech = true;
    }

    else
    {
        HUDComponent->DestroyComponent();
        bIsDetecting = true;

        APMAIController* AIController = Cast<APMAIController>(GetController());
        if (AIController)
        {
            //AIController->SetAimAcceptableRadius(AimAcceptableRadius);
            AIController->SetAsSniper(bIsSniper);
            //AIController->SetEnableBrainComponent(false);
            //FTimerHandle TimerHandle;
            //GetWorld()->GetTimerManager().SetTimer(
            //    TimerHandle,
            //    [this]()
            //    {
            //    },
            //    3.0f,    // 0.1초 지연
            //    false
            //);
        }
    }
    
    RightArmWeaponSlot->SetChildActorClass(APMMechWeapon::StaticClass());
    RightArmWeaponSlot->CreateChildActor();

    LeftArmWeaponSlot->SetChildActorClass(APMMechWeapon::StaticClass());
    LeftArmWeaponSlot->CreateChildActor();

    RightShoulderWeaponSlot->SetChildActorClass(APMMechWeapon::StaticClass());
    RightShoulderWeaponSlot->CreateChildActor();

    LeftShoulderWeaponSlot->SetChildActorClass(APMMechWeapon::StaticClass());
    LeftShoulderWeaponSlot->CreateChildActor();

    /////// 특정 행(Row) 검색, AI처리
    if (bIsPlayerMech)
    {

        UPMGameInstance* GameInstance = Cast<UPMGameInstance>(GetGameInstance());
        //GameInstance->ActivateLoadingScreen();
        FPMMechData CustomizeData = GameInstance->GetMechCustomizeData();

        EquipWeapon(EMechCustomizePart::LeftPrimaryWeapon, CustomizeData.LeftPrimaryWeaponID);
        EquipWeapon(EMechCustomizePart::RightPrimaryWeapon, CustomizeData.RightPrimaryWeaponID);
        EquipWeapon(EMechCustomizePart::LeftShoulderWeapon, CustomizeData.LeftShoulderWeaponID);
        EquipWeapon(EMechCustomizePart::RightShoulderWeapon, CustomizeData.RightShoulderWeaponID);
        HUDComponent->SetRestAPText(FText::AsNumber(StatComponent->GetCurrentAP()));

        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle,
            [this]()
            {
                UPMGameInstance* GameInstance = Cast<UPMGameInstance>(GetGameInstance());
                APlayerController* PlayerController = Cast<APlayerController>(GetController());
                //GameInstance->DisableLoadingScreen();
                FInputModeGameOnly InputMode;
                PlayerController->SetInputMode(InputMode);
            },
            3.0f,    // 0.1초 지연
            false
        );

       
    }
    else
    {
        if (!AILeftArmWeaponID.IsNone())
        {
            EquipWeapon(EMechCustomizePart::LeftPrimaryWeapon, AILeftArmWeaponID);
        }
        if (!AIRightArmWeaponID.IsNone())
        {
            EquipWeapon(EMechCustomizePart::RightPrimaryWeapon, AIRightArmWeaponID);
        }
        if (!AILeftShoulderWeaponID.IsNone())
        {
            EquipWeapon(EMechCustomizePart::LeftShoulderWeapon, AILeftShoulderWeaponID);
        }
        if (!AIRightShoulderWeaponID.IsNone())
        {
            EquipWeapon(EMechCustomizePart::RightShoulderWeapon, AIRightShoulderWeaponID);
        }

    }
}

void APMMechBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsDetecting && !bIsDead)
    {
        Detect();
    }

}

void APMMechBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // 이동 입력 바인딩 (Move 함수 사용)
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APMMechBase::Move);

        // 마우스 회전 입력 바인딩 (Look 함수 사용)
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APMMechBase::Look);

        // 점프 입력 바인딩
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // 무기 사용 입력 바인딩
        EnhancedInputComponent->BindAction(RArmWeaponAction, ETriggerEvent::Triggered, this, &APMMechBase::UseRightWeapon);
        EnhancedInputComponent->BindAction(LArmWeaponAction, ETriggerEvent::Triggered, this, &APMMechBase::UseLeftWeapon);
        EnhancedInputComponent->BindAction(RShoulderWeaponAction, ETriggerEvent::Triggered, this, &APMMechBase::UseRightShoulderWeapon);
        EnhancedInputComponent->BindAction(LShoulderWeaponAction, ETriggerEvent::Triggered, this, &APMMechBase::UseLeftShoulderWeapon);
    }

}



void APMMechBase::HandleHUDInitialized()
{
    UE_LOG(LogTemp, Log, TEXT("HUD Initialized"));
    bIsDetecting = true;
}

void APMMechBase::HandleStatInitialized()
{
    UE_LOG(LogTemp, Log, TEXT("Stat Initialized"));
    if (bIsPlayerMech)
    {
        HUDComponent->SetRestAPText(FText::AsNumber(StatComponent->GetCurrentAP()));
    }
}

void APMMechBase::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void APMMechBase::Look(const FInputActionValue& Value)
{
    FVector2D LookVector = Value.Get<FVector2D>();

    AddControllerYawInput(LookVector.X);
    AddControllerPitchInput(LookVector.Y);
}

float APMMechBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if (bIsDead)
    {
        return 0;
    }
    else
    {
        int32 ResultDamage = Damage;
        StatComponent->DecreaseCurrentAP(Damage);
        if (bIsPlayerMech)
        {
            HUDComponent->SetRestAPText(FText::AsNumber(StatComponent->GetCurrentAP()));
        }

        if (StatComponent->GetCurrentAP() <= 0 && !bIsDead)
        {
            bIsDead = true;
            UPMAnimInstance* MechAnim = Cast<UPMAnimInstance>(GetMesh()->GetAnimInstance());
            MechAnim->SetDeathState();
            GetCharacterMovement()->StopMovementImmediately();
            if (bIsPlayerMech)
            {
                APlayerController* PlayerController = Cast<APlayerController>(GetController());
                FInputModeUIOnly InputMode;
                PlayerController->SetInputMode(InputMode);
            }
        }
        return ResultDamage;
    }
}

void APMMechBase::HandleVictory()
{
    HUDComponent->SetVictoryPanelEnable();
    FTimerHandle TimerHandle;

    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        [this]()
        {
            UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuLevel"));
        },
        5.0f,
        false
    );
}
void APMMechBase::HandleDefeat()
{
    HUDComponent->SetDefeatPanelEnable();
    FTimerHandle TimerHandle;

    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        [this]()
        {
            UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuLevel"));
        },
        5.0f,
        false
    );
}

void APMMechBase::UseRightWeapon()
{
    //TODO: ㄱㄱㄱ
    if (RightArmWeapon && RightArmWeapon->GetbIsInitialized() && MainTarget && !bIsDead)
    {
        RightArmWeapon->Shot(MainTarget->GetActorLocation());
    }
}

void APMMechBase::ReleaseRightWeapon()
{
}

void APMMechBase::UseLeftWeapon()
{
    if (LeftArmWeapon && LeftArmWeapon->GetbIsInitialized() && MainTarget && !bIsDead)
    {
        LeftArmWeapon->Shot(MainTarget->GetActorLocation());
    }
}

void APMMechBase::ReleaseLeftWeapon()
{
}

void APMMechBase::UseRightShoulderWeapon()
{
    if (RightShoulderWeapon && RightShoulderWeapon->GetbIsInitialized() && MainTarget && !bIsDead)
    {
        RightShoulderWeapon->Shot(MainTarget->GetActorLocation());
    }
}

void APMMechBase::ReleaseRightShoulderWeapon()
{

}

void APMMechBase::UseLeftShoulderWeapon()
{
    if (LeftShoulderWeapon && LeftShoulderWeapon->GetbIsInitialized() && MainTarget && !bIsDead)
    {
        LeftShoulderWeapon->Shot(MainTarget->GetActorLocation());
    }
}

void APMMechBase::ReleaseLeftShoulderWeapon()
{

}

void APMMechBase::UpdateLAWeaponAmmoText(FText InAmmoCount)
{
    HUDComponent->SetLAWeaponAmmoText(InAmmoCount);
}

void APMMechBase::UpdateLSWeaponAmmoText(FText InAmmoCount)
{
    HUDComponent->SetLSWeaponAmmoText(InAmmoCount);
}

void APMMechBase::UpdateRAWeaponAmmoText(FText InAmmoCount)
{
    HUDComponent->SetRAWeaponAmmoText(InAmmoCount);
}

void APMMechBase::UpdateRSWeaponAmmoText(FText InAmmoCount)
{
    HUDComponent->SetRSWeaponAmmoText(InAmmoCount);
}

bool APMMechBase::IsInFieldOfView(const AActor* Target)
{
    APlayerCameraManager* CameraManager = Cast<APlayerController>(GetController())->PlayerCameraManager;
    ensure(CameraManager);

    FVector ActorLocation = Target->GetActorLocation();
    FVector2D ScreenPosition;
    
    bool bIsOnScreen = Cast<APlayerController>(GetController())->ProjectWorldLocationToScreen(ActorLocation, ScreenPosition);

    // 카메라의 방향과 비교
    FVector CameraLocation = CameraManager->GetCameraLocation();
    FVector CameraForward = CameraManager->GetCameraRotation().Vector();
    FVector ToActor = (ActorLocation - CameraLocation).GetSafeNormal();

    // 시야각 내에 있는지 확인
    float DotProduct = FVector::DotProduct(CameraForward, ToActor);
    float ViewAngle = FMath::Acos(DotProduct) * (180.0f / PI); // 라디안 → 도 변환

    return ViewAngle <= (CameraManager->GetFOVAngle() / 2.0f);
}

void APMMechBase::Detect()
{
    if (!DetectedTargets.IsEmpty())
    {
        float MinDistance = MAX_FLT;

        for (const auto& EachTarget : DetectedTargets)
        {
            if (bIsPlayerMech)
            {
                if (IsInFieldOfView(EachTarget))
                {
                    float Distance = FVector::Dist(GetActorLocation(), EachTarget->GetActorLocation());
                    if (MinDistance > Distance)
                    {
                        MinDistance = Distance;
                        MainTarget = EachTarget;
                    }
                }
            }
            else
            {
                float Distance = FVector::Dist(GetActorLocation(), EachTarget->GetActorLocation());
                if (MinDistance > Distance)
                {
                    MinDistance = Distance;
                    MainTarget = EachTarget;
                }
            }
        }

        if (MinDistance == MAX_FLT)
        {
            MainTarget = nullptr;
            bIsTargetLockedOn = false;

            UPMAnimInstance* MechAnim = Cast<UPMAnimInstance>(GetMesh()->GetAnimInstance());
            MechAnim->SetAimOffsetMode(EAimOffsetMode::Normal);

            if (bIsPlayerMech)
            {
                HUDComponent->SetFCSModeNormal(FVector(0, 0, 0));
                OnDetectFailed.Broadcast();
            }
            else
            {
                APMAIController* AIController = Cast<APMAIController>(GetController());
                if (AIController)
                {
                    AIController->UpdateMainTarget(nullptr);
                    AIController->UpdateTargetLocation(GetActorLocation());
                    AIController->SetIsInAcceptableDist(false);
                }
            }
        }
    }

    else
    {
        MainTarget = nullptr;
        bIsTargetLockedOn = false;

        UPMAnimInstance* MechAnim = Cast<UPMAnimInstance>(GetMesh()->GetAnimInstance());
        MechAnim->SetAimOffsetMode(EAimOffsetMode::Normal);

        if (bIsPlayerMech)
        {
            HUDComponent->SetFCSModeNormal(FVector(0, 0, 0));
            OnDetectFailed.Broadcast();
        }
        else
        {
            APMAIController* AIController = Cast<APMAIController>(GetController());
            if (AIController)
            {
                AIController->UpdateMainTarget(nullptr);
                AIController->UpdateTargetLocation(GetActorLocation());
                AIController->SetIsInAcceptableDist(false);
            }
        }
    }

    if (MainTarget)
    {
        bIsTargetLockedOn = true;
        //UE_LOG(LogTemp, Log, TEXT("%s: TargetDetected(Target: %s"), *GetName(), *MainTarget->GetName());

        UPMAnimInstance* MechAnim = Cast<UPMAnimInstance>(GetMesh()->GetAnimInstance());
        MechAnim->SetAimOffsetMode(EAimOffsetMode::LockOn, MainTarget->GetActorLocation());

        if (bIsPlayerMech)
        {
            OnDetectSucceeded.Broadcast();
            HUDComponent->SetFCSModeLocked(MainTarget->GetActorLocation());
        }
        else
        {
            APMAIController* AIController = Cast<APMAIController>(GetController());
            if (AIController)
            {
                AIController->UpdateMainTarget(MainTarget);
                AIController->UpdateTargetLocation(MainTarget->GetActorLocation());
                if (FVector::Dist(GetActorLocation(), MainTarget->GetActorLocation()) <= AimAcceptableDist)
                {
                    AIController->SetIsInAcceptableDist(true);
                }
            }
        }
    }
}

void APMMechBase::OnDetectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->Tags[0] != Tags[0])// && OtherActor->ActorHasTag("Enemy")) // 자기 자신 제외
    {
        DetectedTargets.Add(TObjectPtr<AActor>(OtherActor));
        UE_LOG(LogTemp, Warning, TEXT("타겟 감지됨: %s"), *OtherActor->GetName());
    }
}

void APMMechBase::OnDetectEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor)
    {
        DetectedTargets.Remove(TObjectPtr<AActor>(OtherActor));
        UE_LOG(LogTemp, Warning, TEXT("타겟 제거됨: %s"), *OtherActor->GetName());
        if (DetectedTargets.IsEmpty())
        {
            APMAIController* AIController = Cast<APMAIController>(GetController());
            if (AIController)
            {
                AIController->SetIsInAcceptableDist(false);
            }
        }
    }
}

void APMMechBase::EquipWeapon(EMechCustomizePart PartName, FName WeaponID)
{
    UPMGameInstance* GameInstance = Cast<UPMGameInstance>(GetGameInstance());

    UDataTable* WeaponDataTable = GameInstance->GetWeaponDataTable();
    FPMWeaponData* LeftArmWeaponData = nullptr;
    FPMWeaponData* RightArmWeaponData = nullptr;
    FPMWeaponData* LeftShoulderWeaponData = nullptr;
    FPMWeaponData* RightShoulderWeaponData = nullptr;
    switch (PartName)
    {
    case EMechCustomizePart::None:
        return;
        break;
    case EMechCustomizePart::LeftPrimaryWeapon:
        LeftArmWeaponData = (GameInstance->GetWeaponDataTable())->FindRow<FPMWeaponData>(WeaponID, TEXT(""));
        if (!LeftArmWeaponData)
        {
            UE_LOG(LogTemp, Error, TEXT("No matching row found On Left Primary"));
        }

        LeftArmWeapon = Cast<APMMechWeapon>(LeftArmWeaponSlot->GetChildActor());
        if (LeftArmWeapon)
        {
            LeftArmWeapon->InitializeWeaponData(*LeftArmWeaponData, Tags[0]);
            LeftArmWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftArmWeapon"));
            if (bIsPlayerMech)
            {
                LeftArmWeapon->OnWeaponFired.AddDynamic(this, &APMMechBase::UpdateLAWeaponAmmoText);
                HUDComponent->SetLAWeaponNameText(FText::FromString(LeftArmWeaponData->WeaponName));
            }
                //HUDComponent->OnHUDInitialized.AddDynamic(this, &APMMechBase::HandleHUDInitialized);
        }

        break;
    case EMechCustomizePart::RightPrimaryWeapon:
        RightArmWeaponData = (GameInstance->GetWeaponDataTable())->FindRow<FPMWeaponData>(WeaponID, TEXT(""));
        if (!RightArmWeaponData)
        {
            UE_LOG(LogTemp, Error, TEXT("No matching row found On Right Primary"));
        }

        RightArmWeapon = Cast<APMMechWeapon>(RightArmWeaponSlot->GetChildActor());
        if (RightArmWeapon)
        {
            RightArmWeapon->InitializeWeaponData(*RightArmWeaponData, Tags[0]);
            RightArmWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightArmWeapon"));
            if (bIsPlayerMech)
            {
                RightArmWeapon->OnWeaponFired.AddDynamic(this, &APMMechBase::UpdateRAWeaponAmmoText);
                HUDComponent->SetRAWeaponNameText(FText::FromString(RightArmWeaponData->WeaponName));
            }
        }
        break;
    case EMechCustomizePart::LeftShoulderWeapon:

        LeftShoulderWeaponData = (GameInstance->GetWeaponDataTable())->FindRow<FPMWeaponData>(WeaponID, TEXT(""));
        if (!LeftShoulderWeaponData)
        {
            UE_LOG(LogTemp, Error, TEXT("No matching row found On Left Shoulder"));
        }

        LeftShoulderWeapon = Cast<APMMechWeapon>(LeftShoulderWeaponSlot->GetChildActor());
        if (LeftShoulderWeapon)
        {
            LeftShoulderWeapon->InitializeWeaponData(*LeftShoulderWeaponData, Tags[0]);
            LeftShoulderWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftShoulderWeapon"));
            if (bIsPlayerMech)
            {
                LeftShoulderWeapon->OnWeaponFired.AddDynamic(this, &APMMechBase::UpdateLSWeaponAmmoText);
                HUDComponent->SetLSWeaponNameText(FText::FromString(LeftShoulderWeaponData->WeaponName));
            }
        }

        break;
    case EMechCustomizePart::RightShoulderWeapon:

        RightShoulderWeaponData = (GameInstance->GetWeaponDataTable())->FindRow<FPMWeaponData>(WeaponID, TEXT(""));
        if (!RightShoulderWeaponData)
        {
            UE_LOG(LogTemp, Error, TEXT("No matching row found On Right Shoulder"));
        }

        RightShoulderWeapon = Cast<APMMechWeapon>(RightShoulderWeaponSlot->GetChildActor());
        if (RightShoulderWeapon)
        {
            RightShoulderWeapon->InitializeWeaponData(*RightShoulderWeaponData, Tags[0]);
            RightShoulderWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("RightShoulderWeapon"));
            if (bIsPlayerMech)
            {
                RightShoulderWeapon->OnWeaponFired.AddDynamic(this, &APMMechBase::UpdateRSWeaponAmmoText);
                HUDComponent->SetRSWeaponNameText(FText::FromString(RightShoulderWeaponData->WeaponName));
            }
        }

        break;
    default:
        break;
    }



}


//
//void APMMechBase::DoJump()
//{
//    Jump();  // ACharacter 기본 제공 함수 (점프 실행)
//}