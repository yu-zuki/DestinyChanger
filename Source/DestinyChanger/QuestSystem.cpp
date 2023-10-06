//������F2023/08/16�@����ҁF�g�E�@�X�V���e�F�N�G�X�g���K�v�ȍ\���̂��쐬
//������F2023/08/25�@����ҁF�g�E�@�X�V���e�F�N�G�X�g���K�v�Ȋ֐����쐬
//������F2023/08/25�@����ҁF�g�E�@�X�V���e�F�N�G�X�g��UI�Ɋւ���֐����쐬


#include "QuestSystem.h"
#include "DestinyChangerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DestinyChangerGameMode.h"
#include "QuestDatabase.h"
#include "ItemDataBase.h"


// Sets default values for this component's properties
UQuestSystem::UQuestSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ADestinyChangerCharacter* UQuestSystem::GetPlayer()
{
	return Cast<ADestinyChangerCharacter>(UGameplayStatics::GetPlayerCharacter( GetWorld(), 0));
}

ADestinyChangerGameMode* UQuestSystem::GetGameMode()
{
	if (GetWorld() == nullptr) return nullptr;

	if (GameMode == nullptr) {
		GameMode = Cast<ADestinyChangerGameMode>(GetWorld()->GetAuthGameMode());
		return GameMode;
	}

	return GameMode->IsValidLowLevel() ? GameMode : GameMode = Cast<ADestinyChangerGameMode>(GetWorld()->GetAuthGameMode());

}

void UQuestSystem::AddActiveQuest(FName QuestID)
{
	//QuestDatabase����N�G�X�g�����݂��邩�m�F����
	if( !GetGameMode()->GetQuestDatabase()->QuestExists(QuestID) ) return;

	//�A�N�e�B�u�̃N�G�X�g��ǉ�����
	ActiveQuests.Add(QuestID);

	//���s���̃N�G�X�g�ɒǉ�����
	AddExecutingQuest(QuestID);
}

void UQuestSystem::AddCompletedQuest(FName QuestID)
{
	//�����̃N�G�X�g��ǉ�����
	CompletedQuests.Add(QuestID);

	//�A�N�e�B�u�̃N�G�X�g����폜����
	ActiveQuests.Remove(QuestID);

	//���s���̃N�G�X�g����폜����
	ExecutingQuests.Remove(QuestID);

	//Print
	UE_LOG(LogTemp, Warning, TEXT("Completed Quest: %s"), *QuestID.ToString());

	//�N�G�X�g�������������Ƃ�ʒm����
	NotifyExecutingQuestComplete.ExecuteIfBound(QuestID);

	//Exp��ǉ�����
	GetGameMode()->AddExp( GetGameMode()->GetQuestDatabase()->GetQuest(QuestID).QuestDetail.RewardExp );
}

void UQuestSystem::AddExecutingQuest(FName QuestID)
{
	//���s���̃N�G�X�g��ǉ�����
	ExecutingQuests.Add(QuestID);

	//���s���̃N�G�X�g��ǉ��������Ƃ�ʒm����
	UINotifyExecutingQuest.ExecuteIfBound(QuestID);

}

void UQuestSystem::AddQuestItem(FName ItemID, int32 Num)
{
	//ItemBase����A�C�e�������݂��邩�m�F����
	if (!GetGameMode()->GetItemDatabase()->ItemExists(ItemID)) return;

	//QuestItems�ɃA�C�e����ǉ�����
	QuestItems.Add(ItemID, QuestItems.FindRef( ItemID ) + Num);

	//�A�C�e���̐����N�G�X�g�̐��𒴂�����A�N�G�X�g����������B
	//���̂��߁A�S�ẴN�G�X�g���m�F����
	for (auto& QuestID : ExecutingQuests) {
		//QuestDatabase����N�G�X�g���擾����
		FQuestStruct Quest = GetGameMode()->GetQuestDatabase()->GetQuest(QuestID);

		//�N�G�X�g�̃A�C�e����QuestItems�ɑ��݂��邩�m�F����
		if (Quest.QuestDetail.NeedNum > 0) {

			int32 tmp_NowNum = QuestItems.FindRef(Quest.QuestDetail.NeedTargetID);
			int32 tmp_NeedNum = Quest.QuestDetail.NeedNum;
			//�N�G�X�g�̃A�C�e���̐���QuestItems�̐��𒴂�����A�N�G�X�g����������
			if (tmp_NowNum >= tmp_NeedNum){
				AddCompletedQuest(QuestID);
			}
		}
	}
}

void UQuestSystem::AddDefeatRecord(FName EnemyID, int32 Num)
{
}

TArray<FQuestStruct> UQuestSystem::GetActiveQuests()
{	
	//QuestDatabase����A�N�e�B�u�N�G�X�g���擾����
	TArray<FQuestStruct> Quests;
	for (auto& QuestID : ActiveQuests) {
		Quests.Add(GetGameMode()->GetQuestDatabase()->GetQuest(QuestID));
	}
	return Quests;
}

TArray<FQuestStruct> UQuestSystem::GetCompletedQuests()
{
	//QuestDatabase���犮���N�G�X�g���擾����
	TArray<FQuestStruct> Quests;
	for (auto& QuestID : CompletedQuests) {
		Quests.Add(GetGameMode()->GetQuestDatabase()->GetQuest(QuestID));
	}
	return Quests;
}

TArray<FQuestStruct> UQuestSystem::GetExecutingQuests()
{
	//QuestDatabase������s���N�G�X�g���擾����
	TArray<FQuestStruct> Quests;
	for (auto& QuestID : ExecutingQuests) {
		Quests.Add(GetGameMode()->GetQuestDatabase()->GetQuest(QuestID));
	}
	return Quests;
}

int32 UQuestSystem::GetQuestItems(FName ItemID)
{
	//QuestItems ����A�C�e���̐����擾����
	return QuestItems.FindRef(ItemID);
}

int32 UQuestSystem::GetDefeatRecords(FName ItemID)
{
	//DefeatRecords ����G�̐����擾����
	return DefeatRecords.FindRef(ItemID);
}

