// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VNNarrativeNodeBase.h"
#include "VNNarrativeStructs.h" // 包含 FNextNarrativeNode
#include "Engine/StreamableManager.h"	//引入FStreamableHandle的定义
#include "VNDialogueNode.generated.h"

class UTexture2D;
class USoundWave;

/**
 * 具体的对话节点，包含一行的对话内容和资源引用。
 * 使用软指针（TSoftObjectPtr）来避免内存膨胀。
 */
UCLASS(BlueprintType, EditInlineNew)
class VNPRACTICE_API UVNDialogueNode : public UVNNarrativeNodeBase
{
	GENERATED_BODY()

public:
	// 发言人姓名（空表示旁白）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Content")
	FText CharacterName;

	// 对话文本。报告建议使用 Rich Text Block 实现高级样式
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue Content", meta=(MultiLine=true))
	FText DialogueText;

	// 角色立绘。使用软指针
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals")
	TSoftObjectPtr<UTexture2D> CharacterSprite;

	// 角色语音。使用软指针
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TSoftObjectPtr<USoundWave> VoiceLine;

	// --- 流程控制 ---

	// 指向下一个叙事节点的引用
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flow Control")
	FNextNarrativeNode NextNodeReference;
	
	// --- 核心逻辑 ---

	virtual void ExecuteNode_Implementation() override;

protected:
	// 用于跟踪异步加载状态的句柄
	TSharedPtr<FStreamableHandle> AssetLoadHandle;

	// 资产加载完成后的回调函数
	void OnAssetsLoaded();
};