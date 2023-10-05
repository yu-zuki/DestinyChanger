//������F2023/07/08�@����ҁF�g�E�@�������e�F�Q�[���̃��[��

#include "DestinyChangerGameMode.h"
#include "DestinyChangerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "QuestDatabase.h"
#include "ItemDataBase.h"

ADestinyChangerGameMode::ADestinyChangerGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

void ADestinyChangerGameMode::BeginPlay()
{
	//�f�[�^�x�[�X�̐����@�i�����������Ȃ�܂��A����Singleton�Ő݌v����j
	if (QuestDatabaseClass)	{
		QuestDatabaseInstance = GetWorld()->SpawnActor<AQuestDatabase>(QuestDatabaseClass);
	}

	if (ItemDatabaseClass) {
		ItemDatabaseInstance = GetWorld()->SpawnActor<AItemDataBase>(ItemDatabaseClass);
	}

	//Print QuestDatabaseInstance Data
	UE_LOG(LogTemp, Warning, TEXT("Quest Database Initialized."));

	TArray<FQuestStruct> QuestDataArray = QuestDatabaseInstance->AllQuests;
	for (const FQuestStruct& QuestData : QuestDataArray)	{
		UE_LOG(LogTemp, Warning, TEXT("QuestID: %s, Description: %s"), *QuestData.QuestDetail.ID.ToString(), *QuestData.QuestDetail.Description.ToString());
	}

	TArray<FItemStruct> ItemDataArray = ItemDatabaseInstance->AllItems;
	for (const FItemStruct& ItemData : ItemDataArray) {
		UE_LOG(LogTemp, Warning, TEXT("ItemID: %s, Description: %s"), *ItemData.ID.ToString(), *ItemData.Description.ToString());
	}
	

}

/**
 * @brief   EndPlay�֐��́A�Q�[�����[�h�̏I�����ɌĂяo�����֐��ł��B
 *
 * @details AttackEnd�̃f���Q�[�g���N���A���܂��B
 *
 * @return  �Ȃ�
 */
void ADestinyChangerGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	
	//�@�i�@�v���C���[�����̍U���͓G�ɗ^����_���[�W�����݂̂ɂȂ�悤�ɂ��邽�߁A
	//		�U�����I�������G�̃_���[�W�󂯃t���O�����Z�b�g����j
	AttackEnd.Clear();	//	AttackEnd�̃f���Q�[�g���N���A���܂��B
}

/**
 * @brief   AttackEndEventCall�֐��́A�S�Ă̓G�L�����N�^�[���U�����󂯂���悤�ɂ���֐��ł��B
 *
 * @details ���̊֐����Ăяo�����ƂŁA�S�Ă̓G�L�����N�^�[���U�����󂯂���悤�ɂȂ��Ă����܂��B
 *
 * @return  �Ȃ�
 */
void ADestinyChangerGameMode::AttackEndEventCall()
{
	AttackEnd.Broadcast();	//Call �S�Ă̓G���U�����󂯂���悤�ɂ���
}

/**
 * @brief   AddExp�֐��́A�o���l�𑝉������邽�߂̊֐��ł��B
 *
 * @details �v���C���[���擾���A�o���l�𑝉������܂��B
 *
 * @param[in] _Exp ����������o���l
 *
 * @return  �Ȃ�
 */
void ADestinyChangerGameMode::AddExp(float _Exp)
{
	//Player���擾
	ADestinyChangerCharacter* Player = Cast<ADestinyChangerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player)
	{
		Player->AddExp(_Exp);
	}
}

/**
 * @brief   GetQuestDatabase�֐��́AQuestDatabaseInstance��Ԃ��֐��ł��B
 *
 * @details QuestDatabaseInstance������ꍇ�A���̃C���X�^���X��Ԃ��܂��B
 *
 * @return  QuestDatabaseInstance������ꍇ�A���̃C���X�^���X��Ԃ��܂��B����ȊO�̏ꍇ�́Anullptr��Ԃ��܂��B
 */
AQuestDatabase* ADestinyChangerGameMode::GetQuestDatabase()
{
	if (QuestDatabaseInstance)	{
		return QuestDatabaseInstance;
	}

	return nullptr;
}

/**
 * @brief   GetItemDatabase�֐��́AItemDatabaseInstance��Ԃ��֐��ł��B
 *
 * @details ItemDatabaseInstance������ꍇ�A���̃C���X�^���X��Ԃ��܂��B
 *
 * @return  ItemDatabaseInstance������ꍇ�A���̃C���X�^���X��Ԃ��܂��B����ȊO�̏ꍇ�́Anullptr��Ԃ��܂��B
 */
AItemDataBase* ADestinyChangerGameMode::GetItemDatabase()
{
	if (ItemDatabaseInstance) {
		return ItemDatabaseInstance;
	}

	return nullptr;
}
