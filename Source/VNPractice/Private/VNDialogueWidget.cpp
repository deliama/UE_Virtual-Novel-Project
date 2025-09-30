// Fill out your copyright notice in the Description page of Project Settings.


#include "VNDialogueWidget.h"
#include "VNDialogueManagerSubsystem.h" 
#include "Kismet/GameplayStatics.h"
#include "Delegates/Delegate.h" 

void UVNDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 在控件创建时绑定到对话管理器
	BindToDialogueManager();
}

void UVNDialogueWidget::BindToDialogueManager()
{
	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UVNDialogueManagerSubsystem* DialogueManager = GameInstance->GetSubsystem<UVNDialogueManagerSubsystem>())
		{
			// 绑定委托。注意：我们只在 NativeConstruct 绑定一次。
			// 【修正：移除 IsBoundToObject() 检查，避免动态委托的编译错误】
			// if (!DialogueManager->OnDialogueLineReady.IsBoundToObject(this)) 
			{
				DialogueManager->OnDialogueLineReady.AddDynamic(this, &UVNDialogueWidget::OnNewDialogueLine);
			}
		}
	}
}

void UVNDialogueWidget::OnNewDialogueLine(FText CharacterName, FText DialogueText, TSoftObjectPtr<UTexture2D> CharacterSprite, TSoftObjectPtr<USoundWave> VoiceLine)
{
	// 资产已在 DialogueNode 中完成异步加载，此时调用 Get() 是安全的，可以获取有效的硬指针
	UTexture2D* Sprite = CharacterSprite.Get();
	USoundWave* Voice = VoiceLine.Get();
	
	// 调用蓝图事件，将数据传递给 UMG 控件进行显示。
	UpdateDialogueUI(CharacterName, DialogueText, Sprite, Voice);
}