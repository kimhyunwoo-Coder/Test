#include "LS_Icefloor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ULS_Icefloor::ULS_Icefloor()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void ULS_Icefloor::BeginPlay()
{
    Super::BeginPlay();

    OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (OwnerCharacter)
    {
        MoveComp = OwnerCharacter->GetCharacterMovement();
    }
}

void ULS_Icefloor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (MoveComp && OwnerCharacter && IceMaterial)
    {
        UpdateIceSurfaceResponse();
    }
}

void ULS_Icefloor::UpdateIceSurfaceResponse()
{
    FVector Start = OwnerCharacter->GetActorLocation();
    FVector End = Start - FVector(0, 0, 100);

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(OwnerCharacter);

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
    {
        UMaterialInterface* Mat = Hit.Component.IsValid() ? Hit.Component->GetMaterial(0) : nullptr;
        UPhysicalMaterial* DetectedPhysMat = Mat ? Mat->GetPhysicalMaterial() : nullptr;

        // 미끄러짐 판단
        if (DetectedPhysMat == IceMaterial)
        {
            MoveComp->GroundFriction = IceGroundFriction;
            MoveComp->BrakingFrictionFactor = IceBrakingFrictionFactor;
            MoveComp->BrakingDecelerationWalking = IceBrakingDeceleration;
        }
        else
        {
            MoveComp->GroundFriction = DefaultGroundFriction;
            MoveComp->BrakingFrictionFactor = DefaultBrakingFrictionFactor;
            MoveComp->BrakingDecelerationWalking = DefaultBrakingDeceleration;
        }

        // 속도 조정 판단
        if (DetectedPhysMat == FastMaterial)
        {
            MoveComp->MaxWalkSpeed = FastSpeed;
        }
        else if (DetectedPhysMat == SlowMaterial)
        {
            MoveComp->MaxWalkSpeed = SlowSpeed;
        }
        else
        {
            MoveComp->MaxWalkSpeed = DefaultSpeed;
        }
    }
}