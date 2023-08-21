// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManager.h"
#include "Dialogue_UMG.h"

#include "InteractComponent.h"

// Sets default values for this component's properties
UDialogueManager::UDialogueManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogueManager::BeginPlay()
{
	Super::BeginPlay();

	// ...

	//　会話ウィジェットを作成する
	DialogueWidget = CreateWidget<UDialogue_UMG>(GetWorld(), DialogueWidgetClass);
	if (DialogueWidget) {
		DialogueWidget->AddToViewport();
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
}


// Called every frame
void UDialogueManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//会話スタート
void UDialogueManager::StartDialogue()
{
	//会話開始
	bIsDialogueActive = true;

	//　indexを初期化する
	CurrentDialogueIndex = 0;

	// プレイヤーの移動入力を無効化する
	APlayerController* PlayerController =  GetWorld()->GetFirstPlayerController();
	if (PlayerController)	{
		PlayerController->SetIgnoreMoveInput(true);
	}

	//　会話ウィジェットを表示する
	DialogueWidget->SetVisibility(ESlateVisibility::Visible);

	//　次の会話TEXTを表示する
	ShowNextDialogue();

}

//void UDialogueManager::SelectOption(int32 OptionIndex)
//{
//	return;
//}

//　会話があるかどうか
bool UDialogueManager::HasDialogueToDisplay() const
{
	return DialogueData.IsValidIndex(CurrentDialogueIndex);
}

//　次の会話を表示する
void UDialogueManager::ShowNextDialogue()
{
	if (HasDialogueToDisplay())	{
		FDialogueNode CurrentNode = GetNextDialogueNode();

		if (!CurrentNode.SpeakerName.IsEmpty()) {
			//　会話ウィジェットに会話データをセットする
			DialogueWidget->SetSpeakerName(CurrentNode.SpeakerName);
			DialogueWidget->SetDialogueText(CurrentNode.DialogueText);
		}
	}
	else	{
		//会話終了
		bIsDialogueActive = false;

		//　会話が終わったらプレイヤーの移動入力を有効化する
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)		{
			PlayerController->ResetIgnoreMoveInput();
		}
		//　会話が終わったら会話ウィジェットを非表示にする
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);


	}
}

FDialogueNode UDialogueManager::GetNextDialogueNode()
{
	if (DialogueData.IsValidIndex(CurrentDialogueIndex))	{
		CurrentDialogueIndex++;
		return DialogueData[CurrentDialogueIndex - 1];
	}
	else	{
		FDialogueNode EmptyNode;
		return EmptyNode;
	}
}

void UDialogueManager::EnterDialogue(AActor* _Caller)
{

	if (!bIsDialogueActive) {
		StartDialogue();
	}
	else {
		ShowNextDialogue();
	}

	if (_Caller != nullptr) {
		_Caller->FindComponentByClass<UInteractComponent>()->SetUIActive(!bIsDialogueActive);
	}
}

