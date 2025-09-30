// Fill out your copyright notice in the Description page of Project Settings.


#include "VNDialogueManagerSubsystem.h"
#include "VNNarrativeNodeBase.h"
#include "Engine/AssetManager.h"


void UVNDialogueManagerSubsystem::StartNarrative(UVNNarrativeNodeBase* StartNode)
{
	if (!StartNode)
	{
		UE_LOG(LogTemp, Error, TEXT("Attempted to start narrative with a null node!"));
		return;
	}

	CurrentNode = StartNode;
	// 开始执行第一个节点
	CurrentNode->ExecuteNode();
}

void UVNDialogueManagerSubsystem::AdvanceNarrative()
{
	// 1. 检查是否有当前节点
	if (!CurrentNode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to advance narrative but CurrentNode is null. Story finished or not started."));
		return;
	}

	// 2. 假设当前节点执行完毕后，获取下一个节点引用（这通常会在 ExecuteNode 中设置）
	// 注意：在完整实现中，VNNarrativeNodeBase 的子类（如VNDialogueNode）会有一个 FNextNarrativeNode 成员。
	// 为了 Demo 简化，我们假设 CurrentNode 上有一个 GetNextNode 方法。
	// 由于我们现在还没有具体的 Dialogue Node 实现，此处仅为框架演示。

	// 理想情况下：
	/*
	if (UVNDialogueNode* DialogueNode = Cast<UVNDialogueNode>(CurrentNode))
	{
		NextNodeReference = DialogueNode->NextNodeReference; // 假设 DialogueNode 有一个 NextNodeReference 成员
		LoadNextNodeAndAdvance(NextNodeReference);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CurrentNode is not a Dialogue Node and cannot advance automatically."));
	}
	*/
	
	// 暂时跳过复杂的加载逻辑，等待 DialogueNode 完成
	// 在实际原型中，我们会让当前节点处理完后，再异步加载并切换到下一个节点。
	
	UE_LOG(LogTemp, Log, TEXT("Advancing narrative... (Placeholder)"));
}

void UVNDialogueManagerSubsystem::LoadNextNodeAndAdvance(const FNextNarrativeNode& NextNodeRef)
{
	if (!NextNodeRef.NextNode.IsNull())
	{
		// 报告建议使用 FStreamableManager 或 UAssetManager 进行异步加载
		UAssetManager& Manager = UAssetManager::Get();
		
		TArray<FSoftObjectPath> AssetsToLoad;
		AssetsToLoad.Add(NextNodeRef.NextNode.ToSoftObjectPath());
		
		Manager.LoadAssetList(
			AssetsToLoad, 
			FStreamableDelegate::CreateLambda([this, NextNodeRef]()
			{
				UVNNarrativeNodeBase* LoadedNode = NextNodeRef.NextNode.Get();
				if (LoadedNode)
				{
					// 加载成功，切换到新节点并执行
					CurrentNode = LoadedNode;
					CurrentNode->ExecuteNode();
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to load next narrative node."));
				}
			})
		);
	}
	else
	{
		// 流程结束
		CurrentNode = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Narrative stream ended. Next node is null."));
	}
}