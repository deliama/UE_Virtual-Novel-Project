// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "VNNarrativeStructs.generated.h"

class UVNNarrativeNodeBase;

/**
 * 软引用指针，指向故事中的下一个节点。
 * 使用 TSoftObjectPtr 来避免硬引用，实现异步加载，优化内存。
 */
USTRUCT(BlueprintType)
struct FNextNarrativeNode
{
	GENERATED_BODY()

	// 软对象指针，指向下一个要加载和执行的叙事节点。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Narrative")
	TSoftObjectPtr<UVNNarrativeNodeBase> NextNode;

	// 构造函数
	FNextNarrativeNode() {}
};