//制作日：2023/09/28　制作者：トウ　更新内容：アイテムのデータベース


#include "ItemDataBase.h"

bool AItemDataBase::ItemExists(FName ID) const
{
	//アイテムのIDが存在するかどうかを返す
	return AllItems.ContainsByPredicate(
		[&](const FItemStruct& Item) {
			return Item.ID == ID;
		}
	);
}

FItemStruct AItemDataBase::GetItem(FName ID) const
{
	//アイテムを返す
	const FItemStruct* FoundItem = AllItems.FindByPredicate(
		[&](const FItemStruct& Item) {
			return Item.ID == ID;
		}
	);

	return FoundItem ? *FoundItem : FItemStruct();
}
