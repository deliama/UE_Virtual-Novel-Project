// Fill out your copyright notice in the Description page of Project Settings.


#include "VNPlayerPawn.h"

// Sets default values
AVNPlayerPawn::AVNPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVNPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVNPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVNPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

