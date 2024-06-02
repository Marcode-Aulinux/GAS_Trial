// Copyright Marcode Aulinux


#include "Actor/AuraEffectActor.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToActor(AActor* Actor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Use UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent to get the AbilitySystemComponent from the Actor
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
	// safeguard
	if (TargetAbilitySystemComponent == nullptr)
	{
		return;
	}

	check(GameplayEffectClass);
	// Create a GameplayEffectContextHandle
	FGameplayEffectContextHandle EffectContext = TargetAbilitySystemComponent->MakeEffectContext();
	// Set the SourceObject to this Actor
	EffectContext.AddSourceObject(this);
	// Make the GameplayEffectSpec
	FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1, EffectContext);
	// Apply the GameplayEffectSpec to the Actor
	// We need to dereference the Data pointer to get the FGameplayEffectSpec because FGameplayEffectSpecHandle is a TSharedPtr
	TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
}
