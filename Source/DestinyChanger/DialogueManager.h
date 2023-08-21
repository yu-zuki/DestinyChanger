﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueManager.generated.h"

USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		FText SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		FText DialogueText;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINYCHANGER_API UDialogueManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void StartDialogue(); // 会話スタート

	//UFUNCTION(BlueprintCallable, Category = "Dialogue")
	//	void SelectOption(int32 OptionIndex); // 選択肢を選ぶ

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		bool HasDialogueToDisplay() const; // 会話があるかどうか

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void  ShowNextDialogue();		  // 次の会話を表示する

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		FDialogueNode GetNextDialogueNode(); // 次の会話ノードを取得する

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		TArray<FDialogueNode> DialogueData; // 会話データ

	int32 CurrentDialogueIndex; // 今の会話ノードのインデックス

	//Flag
	bool bIsDialogueActive; // 会話がアクティブかどうか

public:
	//入口
	void EnterDialogue(AActor* _actor = nullptr); // 会話に入る

	//GetFlag
	bool GetIsDialogueActive() const { return bIsDialogueActive; } // 会話がアクティブかどうかを取得する
		
//////////////////////////////////////////////////////////////////////////
// UMG
protected:
		class UDialogue_UMG* DialogueWidget; // 会話ウィジェット

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		TSubclassOf<class UDialogue_UMG> DialogueWidgetClass; // 会話ウィジェットのクラス

};
