// Fill out your copyright notice in the Description page of Project Settings.


#include "VNNarrativeNodeBase.h"

void UVNNarrativeNodeBase::ExecuteNode_Implementation()
{
	// 默认实现为空，具体逻辑由子类（如对话节点、选项节点）在蓝图中实现
	// 或者在下一步创建的 DialogueManager 中通过 C++ 进一步处理
	UE_LOG(LogTemp, Warning, TEXT("Executing base narrative node: %s"), *GetName());
}