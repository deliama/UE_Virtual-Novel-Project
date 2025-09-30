// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagContainer.h"
#include "VNGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VNPRACTICE_API UVNGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UVNGameInstance();

	//全局叙事标志容器
	//用来存储玩家在整个故事中解锁或改变的状态（如：好感度、已完成任务等）
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Narrative")
	FGameplayTagContainer GlobalNarrativeTags;

	//覆写Init，这里可以初始化全局管理器，例如音频管理器，存档管理器等
	virtual void Init() override;
	
};
