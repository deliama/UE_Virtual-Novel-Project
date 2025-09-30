// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VNNarrativeNodeBase.generated.h"

/**
 * 所有叙事节点（对话、选项、分支等）的基类。
 * 报告建议使用 UDataAsset 管理故事流程，以实现内存优化。
 */
UCLASS(Abstract, BlueprintType, EditInlineNew)
class VNPRACTICE_API UVNNarrativeNodeBase : public UDataAsset
{
	GENERATED_BODY()

public:
	// 虚函数，供 DialogueManager 调用以执行节点逻辑
	// 在子类中实现具体的行为（如显示对话，显示选项等）
	UFUNCTION(BlueprintNativeEvent, Category = "Narrative")
	void ExecuteNode();
	virtual void ExecuteNode_Implementation();
};