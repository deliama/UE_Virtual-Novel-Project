// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VNDialogueWidget.generated.h"

class UTexture2D;
class USoundWave;

/**
 * 核心对话UI控件，负责接收 DialogueManager 的数据并显示。
 */
UCLASS()
class VNPRACTICE_API UVNDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// UMG 绑定的函数：在蓝图中实现，用于更新 UI 文本和图像
	// 注意参数是硬指针，因为在调用此函数前，资产已在 DialogueNode 中异步加载完毕。
	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue UI")
	void UpdateDialogueUI(const FText& CharacterName, const FText& DialogueText, UTexture2D* CharacterSprite, USoundWave* VoiceLine);

protected:
	virtual void NativeConstruct() override;

private:
	// 绑定 DialogueManager 的委托
	void BindToDialogueManager();

	// DialogueManager 委托触发时调用的函数
	UFUNCTION()
	void OnNewDialogueLine(FText CharacterName, FText DialogueText, TSoftObjectPtr<UTexture2D> CharacterSprite, TSoftObjectPtr<USoundWave> VoiceLine);
};