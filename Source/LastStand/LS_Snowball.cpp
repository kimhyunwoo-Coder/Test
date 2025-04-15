#include "LS_Snowball.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actor_Component/LS_KnockbackComponent.h"

ALS_Snowball::ALS_Snowball()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    Mesh->SetSimulatePhysics(true);
    Mesh->SetNotifyRigidBodyCollision(true);
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    // 버튼 못 누르게: 트리거 채널 무시 설정 (버튼이 감지하는 채널 무시)
    Mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore); // 예: 버튼이 GameTraceChannel1이라면
    Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore); // 버튼이 Pawn을 감지한다면 이것도 무시
    Mesh->SetCollisionObjectType(ECC_PhysicsBody); // 충돌 채널 분리해도 좋음
}

void ALS_Snowball::BeginPlay()
{
    Super::BeginPlay();

    Mesh->OnComponentHit.AddDynamic(this, &ALS_Snowball::OnHit);
}

void ALS_Snowball::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        if (OtherActor->ActorHasTag("Player"))
        {
            if (ULS_KnockbackComponent* Knockback = OtherActor->FindComponentByClass<ULS_KnockbackComponent>())
            {
                Knockback->ApplyKnockback(GetActorLocation(), 5000.0f, 0.6f);
            }
        }

        if (HitSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
        }

        if (HitEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorTransform());
        }

        Destroy();
    }
}