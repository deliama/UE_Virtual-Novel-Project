// Fill out your copyright notice in the Description page of Project Settings.


#include "VNDialogueNode.h"
#include "VNDialogueManagerSubsystem.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"

void UVNDialogueNode::ExecuteNode_Implementation()
{
	Super::ExecuteNode_Implementation();

	UE_LOG(LogTemp, Log, TEXT("Executing Dialogue Node: %s"), *GetName());
	
	// 1. 收集需要异步加载的资源列表
	TArray<FSoftObjectPath> AssetsToLoad;
	if (!CharacterSprite.IsNull())
	{
		AssetsToLoad.Add(CharacterSprite.ToSoftObjectPath());
	}
	if (!VoiceLine.IsNull())
	{
		AssetsToLoad.Add(VoiceLine.ToSoftObjectPath());
	}
	
	// 2. 异步加载资源
	if (AssetsToLoad.Num() > 0)
	{
		UAssetManager& Manager = UAssetManager::Get();
		// 使用 AssetManager 异步加载所有软引用资源
		AssetLoadHandle = Manager.LoadAssetList(
			AssetsToLoad, 
			FStreamableDelegate::CreateUObject(this, &UVNDialogueNode::OnAssetsLoaded)
		);
	}
	else
	{
		// 没有需要加载的资源，立即执行下一步：广播数据
		OnAssetsLoaded();
	}
}

void UVNDialogueNode::OnAssetsLoaded()
{
	// 1. 获取 DialogueManager Subsystem
	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GWorld))
	{
		if (UVNDialogueManagerSubsystem* DialogueManager = GameInstance->GetSubsystem<UVNDialogueManagerSubsystem>())
		{
			// 2. 广播数据给 UMG Widget
			DialogueManager->OnDialogueLineReady.Broadcast(
				CharacterName, 
				DialogueText, 
				CharacterSprite, 
				VoiceLine
			);
			
			// 3. 释放 AssetLoadHandle（加载完成）
			if (AssetLoadHandle.IsValid())
			{
				AssetLoadHandle->ReleaseHandle();
			}
		}
	}
}