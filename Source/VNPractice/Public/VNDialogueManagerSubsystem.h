// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "VNNarrativeStructs.h"
#include "VNDialogueManagerSubsystem.generated.h"

class UVNNarrativeNodeBase;
class UTexture2D;
class USoundWave;

//定义委托，用于将新对话行数广播给UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
	FOnDialogueLineReady,
	FText,
	CharacterName,
	FText,
	DialogueText,
	TSoftObjectPtr<UTexture2D>,
	CharacterSprite,
	TSoftObjectPtr<USoundWave>,
	VoiceLine);

/**
 * 叙事对话管理子系统，负责控制故事流程、处理节点数据和与UI通信
 */
UCLASS()
class VNPRACTICE_API UVNDialogueManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	//委托实例，UMG Widget将订阅该委托来更新显示
	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnDialogueLineReady OnDialogueLineReady;

	//核心函数：开始故事
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartNarrative(UVNNarrativeNodeBase* StartNode);

	//核心函数：推进到下一行对话或节点
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AdvanceNarrative();

	//当前正在执行的叙事节点
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly, Category = "Dialogue")
	TObjectPtr<UVNNarrativeNodeBase> CurrentNode;

protected:
	//队列：用于异步加载下一节点临时存放的指针
	FNextNarrativeNode NextNodeReference;

	//异步加载下一节点：实现异步资产加载的关键
	void LoadNextNodeAndAdvance(const FNextNarrativeNode& NextNodeRef);
	
};
