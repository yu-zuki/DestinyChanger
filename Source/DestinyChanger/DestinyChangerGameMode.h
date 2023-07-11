//制作日：2023/07/08　制作者：トウ　処理内容：ゲームのルールとツールメソッド
//制作日：2023/07/08　制作者：トウ　更新内容：委託イベントの追加

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DestinyChangerGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE(AttackEndEventSignature);

UCLASS(minimalapi)
class ADestinyChangerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADestinyChangerGameMode();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	AttackEndEventSignature AttackEnd;			

	template <typename ObjectType, typename MethodType>
	void AttackEndEventBind(ObjectType* Object, MethodType Method);

	void AttackEndEventCall();
};

template<typename ObjectType, typename MethodType>
inline void ADestinyChangerGameMode::AttackEndEventBind(ObjectType* Object, MethodType Method)
{
	AttackEnd.AddUObject(Object, Method);
}
