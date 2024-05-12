// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyAttackState.h"
#include "../Character/PJECharacterBase.h"
#include "../Character/Component/HealthComponent.h"


//���� ���� ���� �ִ� ����� ã�� �������� ����
void UAnimNotifyAttackState::TryAttack(USkeletalMeshComponent* MeshComp)
{
	if (CurrentAttackCount >= 1)
		return;

	APJECharacterBase* MyCharacter = Cast<APJECharacterBase>(MeshComp->GetOwner());
	TArray<APJECharacterBase*> TargetCharacters;

	if (TryGetOverlapTargets(MyCharacter, TargetCharacters))
	{
		for (auto* TargetCharacter : TargetCharacters)
		{
			UHealthComponent* DamagedHealthComponent = TargetCharacter->FindComponentByClass<UHealthComponent>();
			if (DamagedHealthComponent)
			{
				DamagedHealthComponent->ChangeHealth(-DamageAmount);
			}
		}
	}
}

void UAnimNotifyAttackState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	CurrentAttackCount = 0;
	TryAttack(MeshComp);
}

void UAnimNotifyAttackState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	TryAttack(MeshComp);
}

void UAnimNotifyAttackState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	CurrentAttackCount = 0;
}

//�־��� ĳ������ ��ġ�� �߽����� ���� ���� �ִ� ĳ���͸� �˻�
bool UAnimNotifyAttackState::TryGetOverlapResult(APJECharacterBase* Owner, TArray<FOverlapResult>& OverlapResults)
{
	auto* World = Owner ? Owner->GetWorld() : nullptr;
	if (World == nullptr)
		return false;

	FVector Center = Owner->GetActorLocation();
	FCollisionQueryParams CollisionParam(NAME_None, false, Owner);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center + CenterOffset,
		Owner->GetActorQuat(),
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(600.0f),
		CollisionParam);

	return bResult;
}

//�־��� ĳ���͸� �߽����� ���� ���� ���� �ִ� ����� �˻�
bool UAnimNotifyAttackState::TryGetOverlapTargets(APJECharacterBase* Character, OUT TArray<APJECharacterBase*>& FoundTargets)
{
	TArray<FOverlapResult> OverlapResults;
	bool bResult = false;

	if (TryGetOverlapResult(Character, OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = GetCharacter(OverlapResult);
			if (TargetCharacter == nullptr)
				continue;

			bResult = true;
			FoundTargets.Add(TargetCharacter);
			break;
		}
	}

	return bResult;
}
