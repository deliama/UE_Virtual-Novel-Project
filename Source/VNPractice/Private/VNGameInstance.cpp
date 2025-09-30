// Fill out your copyright notice in the Description page of Project Settings.


#include "VNGameInstance.h"

UVNGameInstance::UVNGameInstance()
{
}

void UVNGameInstance::Init()
{
	Super::Init();

	// 在此处可以执行 GameInstance 的初始化逻辑
	UE_LOG(LogTemp, Log, TEXT("UVNGameInstance initialized."));
}
