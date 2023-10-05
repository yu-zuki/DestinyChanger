//������F2023/09/28�@����ҁF�g�E�@�X�V���e�F�A�C�e���̃f�[�^�x�[�X


#include "ItemDataBase.h"

bool AItemDataBase::ItemExists(FName ID) const
{
	//�A�C�e����ID�����݂��邩�ǂ�����Ԃ�
	return AllItems.ContainsByPredicate(
		[&](const FItemStruct& Item) {
			return Item.ID == ID;
		}
	);
}

FItemStruct AItemDataBase::GetItem(FName ID) const
{
	//�A�C�e����Ԃ�
	const FItemStruct* FoundItem = AllItems.FindByPredicate(
		[&](const FItemStruct& Item) {
			return Item.ID == ID;
		}
	);

	return FoundItem ? *FoundItem : FItemStruct();
}
