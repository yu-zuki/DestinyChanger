# DestinyChanger

- **開発形態**: 個人制作
- **ジャンル**: ARPG
- **開発期間**: 2023年7月8日 ～ 2023年10月9日
- **制作内容**: 3DモデリングとBGM、そしてミニマップにはUEのアセットを利用し、それ以外の部分は全て個人で制作しました。

[→プレイ動画](#プレイ動画)

[→実行ファイルダウンロード](#実行ファイルのダウンロード)
## 1. プロジェクトの概要

趣味としてARPG（アクションロールプレイングゲーム）を制作しました！

このプロジェクトは、TGSのプロジェクトに参加していた期間と並行して、プライベートの時間を利用して制作されました。ARPGの構造に興味を持っていたため、このジャンルのゲーム作成に挑戦しました。現在は制作途中であり、今後はスキルやシーンの演出を充実させ、さらにドラゴンの敵を追加する予定です。


## 2. 技術的詳細
- **プログラミング言語**: C++
- **フレームワーク/エンジン**: Unreal Engine 5.1.1
- **使用ツール**: 例: Visual Studio, Visual Studio Code, git, github, photoshop

## 3. 機能説明
 
### バトルシステム
バトルシステムはプレイヤーのゲーム体験を向上させるためのいくつかの要素を取り入れて設計されています。

- **コンボの体験**: モーションが終わった後でも、時間の制限が厳しくないため、プレイヤーはコンボを続けることができます。
  
- **攻撃しやすさ（角度編）**: 敵に対しての位置取りが自動で調整され、敵が後ろにいてもプレイヤーはその方向に向き直ります。これにより、ゲームプレイがスムーズになります。
  
- **攻撃しやすさ（距離編）**: 敵との距離がある程度あっても、プレイヤーは自動的に前進して攻撃することができます。これにより、遠くの敵にも効果的に攻撃することができます。
  
- **回避アクション**: 攻撃直後でも、プレイヤーはすぐに回避行動を取ることができます。これにより、戦略的なバトルが可能になります。
  
- **マップ外の敵**: マップの外側からの敵の攻撃は、UIで明確に示されます。これにより、プレイヤーは予期しない攻撃から守ることができます。

- **打撃感**: 敵を攻撃する際、ヒットストップが発生し、敵に微かな移動が発生することで、打撃のリアルな感覚を提供します。

[→バトルシステムのコードを参照](#バトルシステムのコード部分)

![動画](Document/Battle.gif)


### デスティニーシステム  
ディスティニーシステムは、プレイヤーが敵の攻撃をガードした際に、一時的にプレイヤーの攻撃力を増加させるシステムです。攻撃力の増加倍率は、時間の経過とともに徐々に減少します。また、このシステムの効果時間には上限が存在します。

このシステムは、プレイヤーが戦略的なガードを成功させた際に、一時的な攻撃力のブーストを提供することで、ゲームプレイのダイナミクスを高める効果が期待されます。

[→ディスティニーシステムのコードを参照](#ディスティニーシステムに関連する主要なコードの部分です)

![動画](Document/Destiny.gif)


### エネミーシステム
さまざまな種類の敵キャラクターがゲーム内に登場します。それぞれに独自の攻撃パターンと戦略があります。（まだ1種類しか実装してません。）

[→エネミーシステムのコードを参照](#エネミーシステムのコード部分)

![動画](Document/Enemy.gif)


### UIシステム
ゲームの進行状況、キャラクターの状態、敵の位置や方向などの情報をプレイヤーに表示します。

[→UIシステムのコードを参照](#UIシステムのコード部分)

![動画](Document/UI.gif)


### 会話システム
NPCとの対話を通じて、ストーリーが進行します。

[→会話システムのコードを参照](#会話システムのコード部分)

![動画](Document/Quest.gif)


### クエストシステム
クエストを通じて、プレイヤーはゲーム内のミッションを完了することができます。

[→クエストシステムのコードを参照](#クエストシステムのコード部分)

![動画](Document/Quest.gif)


### 簡単な仕様図
![簡単な説明図](Document/ARPG.png)


## 4. ソースコードの説明とサンプル

### バトルシステムのコード部分
バトルシステムは、攻撃処理、武器の装備、モーションの切り替え、武器の当たり判定生成、回避処理、ダメージ受け処理、ガード処理、HitStop、およびHitEffectなどの複数のコンポーネントから構成されています。ここでは、コンポーネントが多数あるため、主要な攻撃処理のみを紹介します。

- **プレイヤーは攻撃する時**
まず、攻撃角度を調整し、攻撃フラグを有効にしてから、AnimMontageを再生します。特定のフレーム間でHitDetect関数を呼び出し、この関数内で武器ClassのCheckOverlap()メソッドを呼び出し、フレームごとにCapsuleコリジョンを生成します。このコリジョンが敵と交差した場合、ダメージを与えます。最適化のため、特定のフレーム間でのみ当たり判定を行っています。

```cpp
//ファイル：DestinyChangerCharacter.cpp

/**
 * @brief   LightAttackアクションのコールバックです。
 *
 * @details インタラクト可能オブジェクトがある場合はインタラクトを呼び出し終了する。
 *			武器を持っていない場合は装備します。
 *          武器を持っている場合、isAttackingフラグを立てて攻撃を開始し、攻撃コンボを1つカウントアップします。
 *
 * @param   Value InputActionValue
 *
 * @return  なし
 */
void ADestinyChangerCharacter::LightAttack(const FInputActionValue& Value)
{
	if (AActor* InteraObj = InteractComponent->GetInteractObject()) {
		//Cast
		if (IInteractableAPI* InteractableObject = Cast<IInteractableAPI>(InteraObj)) {
			InteractableObject->Interact(this);
			return;
		}
	}

	//武器を持っている場合は武器の切り替えを行う
	if (MainWeapon) {
		if (MainWeapon->GetIsAttachToHand()) {												//武器を持っているかどうか
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance && AnimInstance->Montage_IsPlaying(AnimMontage_WeaponDraw))	//武器を装備するアニメーションを再生中ならreturn
				return;

			PlayAnimMontage(AnimMontage_WeaponDraw);										//持ってない場合、武器を装備するアニメーションを再生	
			return;
		}
	}

	//攻撃中ではない時のみ攻撃を行う
	if (!bIsAttacking) {
		//Attack Assist Componentで角度を修正
		AttackAssistComponent->CorrectAttackAngle();

		//play light attack animation
		if (LightAttackMontageOne && LightAttackMontageTwo && LightAttackMontageThree && LightAttackMontageFour) {
			switch (eAttackComb)
			{
			case EAttackComb::LightAttackOne:
				PlayAnimMontage(LightAttackMontageOne);
				break;
			case EAttackComb::LightAttackTwo:
				PlayAnimMontage(LightAttackMontageTwo);
				break;
			case EAttackComb::LightAttackThree:
				PlayAnimMontage(LightAttackMontageThree);
				break;
			case EAttackComb::LightAttackFour:
				PlayAnimMontage(LightAttackMontageFour);
				break;
			}		

			bIsAttacking = true;	//set attacking to true
			LightAttackCountUp();	//次の攻撃に備えてカウントアップ
		}
	}

}

void ADestinyChangerCharacter::HitDecect()
{
	//hit detect
	MainWeapon->CheckOverlap();
}
```

```cpp
//ファイル：Attacking_AN.cpp

void UAttacking_AN::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//PlayerGet
	ADestinyChangerCharacter* Player = Cast<ADestinyChangerCharacter>(MeshComp->GetOwner());
	if (Player)	{
		Player->HitDecect();
	}
}
```

```cpp
//ファイル：BaseWeapon.cpp

//チェック
//チェック　当たり判定用のコリジョンを生成
void ABaseWeapon::CheckOverlap()
{
	TArray<FHitResult> HitResults;				//ヒットしたものを格納する配列
	FCollisionQueryParams CollisionParams;	
	CollisionParams.AddIgnoredActor(this);		//自分自身を無視する

	FVector Start = WeaponCollision->GetComponentLocation();	//生成したコリジョンの中心位置
	FVector End = Start;// + GetActorForwardVector() * 100.0f;　
	FQuat Rot = WeaponCollision->GetComponentQuat();			//生成したコリジョンの向き

	//コリジョンの形状を取得（　武器クラスで作ったカプセルコンポーネントから　）
	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(WeaponCollision->GetScaledCapsuleRadius(), WeaponCollision->GetScaledCapsuleHalfHeight());


	//当たり判定を行う、ヒットしたものをHitResultsに格納
	bool isHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, Rot, ECollisionChannel::ECC_GameTraceChannel1, CollisionShape, CollisionParams);
	
	//if (isHit != true) { return; }

	//Debug
	if (false)	{
		DrawDebugCapsule(GetWorld(), (Start + End) / 2,
			CollisionShape.GetCapsuleHalfHeight(),
			CollisionShape.GetCapsuleRadius(), Rot, FColor::Red, true, -1.0f, 0, 1.0f);
	}

	//HitResultsに格納されたものを一つずつ処理
	for (FHitResult HitResult : HitResults)	{
		EnemyOnOverlap(HitResult);
	}
}

//敵との当たり判定
void ABaseWeapon::EnemyOnOverlap(FHitResult& _HitResult)
{
	//Cast
	AEnemyBase* Enemy = Cast<AEnemyBase>(_HitResult.GetActor());
	if (Enemy) {
		if (Enemy->bIsAttacked) {
			return;
		}

		AActor* Player = GetOwner();			
		if (Player) {
			ADestinyChangerCharacter* DestinyChangerCharacter = Cast<ADestinyChangerCharacter>(Player);

			/////////////////////////////////////////
			//敵にダメージを与える
			Enemy->Damage(fAttackPower * DestinyChangerCharacter->GetPower());


			/////////////////////////////////////////
			//プレイヤーのヒットストップ処理
			FVector HitLocation = _HitResult.Location;		//ヒットエフェクトの位置

			if (DestinyChangerCharacter) {
				DestinyChangerCharacter->GetAttackAssistComponent()->HitStop();
				DestinyChangerCharacter->GetAttackAssistComponent()->HitEffect(HitEffect,HitLocation,GetActorForwardVector());
			}
		}
		//Debug
		FQuat Rotation = FQuat::Identity;
		FVector Extent = FVector(5, 5, 5);

		//DrawDebugBox(GetWorld(), HitLocation, Extent, Rotation, FColor::Green, false, 5.0f, 0, 1.0f);
		//Enemyの名前とHPをPrintStringで表示
		FString OutputString = FString::Printf(TEXT("Enemy: %s, Health: %f"), *Enemy->GetName(), Enemy->GetHP());
		UKismetSystemLibrary::PrintString(this, OutputString);
	}
}
```

### ディスティニーシステムに関連する主要なコードの部分です。

```cpp
//ファイル：DestinyChangerCharacter.h
protected:
	//DestinySystem一回起動すると増える時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DestinySystem", meta = (AllowPrivateAccess = "true"))
		float fDestinySystemAddTime;
	
	//DestinySystemの最大時間
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DestinySystem", meta = (AllowPrivateAccess = "true"))
		float fDestinySystemTimeMax;

	//DestinySystemが一回発動
	void ExecuteDestinySystem();

	//タイマーに設定する時間
	float fDestinySystemTimerLength = 0.f;

	//タイマーに設定する時間を増やす
	void AddDestinySystemTimerLength();

	//TimerHandle
	FTimerHandle DestinySystemTimerHandle;

	//AttackPowerReset
	void AttackPowerReset();

	//Create AttackPowerReset Timer
	void CreateAttackPowerResetTimer();

	//AttackPowerの倍率
	float fDefaultAttackPowerRatio = 2.1f;

	float fAttackPowerRatio;

	//AttackPowerの倍率をリセット
	void AttackPowerRatioReset();

	//Get AttackPowerRatio
	float GetAttackPowerRatio();
```

機能詳細:
- **DestinySystemの起動時の時間増加**: `fDestinySystemAddTime` は、ディスティニーシステムが一度起動すると増加する時間を指定します。
- **DestinySystemの最大時間**: `fDestinySystemTimeMax` は、ディスティニーシステムの効果が継続する最大時間を定義します。
- **DestinySystemの実行**: `ExecuteDestinySystem()` 関数は、ガード成功時に攻撃力を倍増させる処理を行います。
- **タイマーの設定時間の追加**: `AddDestinySystemTimerLength()` 関数は、ディスティニーシステムの効果時間を増加させる処理を行います。
- **攻撃力のリセット**: `AttackPowerReset()` 関数は、ディスティニーシステムの効果が終了した際に、攻撃力の倍率を元に戻す処理を行います。
- **攻撃力倍率の取得**: `GetAttackPowerRatio()` 関数は、現在の攻撃力の倍率を取得する処理を行います。

### エネミーシステムのコード部分
エネミーシステムの構造は、Behavior Tree、AIController、Blackboard（AIのデータ）、AnimNotifyState（アニメーションが特定フレーム時の通知）、およびTaskNode（Taskの処理）の5つのコンポーネントから構成されています。

今回、Behavior TreeのBlackboardにはEnemyのステートのみが含まれており、各TaskNodeの処理やステートの切り替えは全てC++側で制御されています。

- **エネミーAIのBehavior Treeの処理**
![Behavior Treeのスクリーンショット](Document/EnemyAIBT.png)

- **エネミーAIのBlackboardの構造**
![Blackboardのスクリーンショット](Document/AIEnemy_BD.png)

- **エネミーAIのTaskNode処理の一例**
  
この処理では、Enemyがプレイヤーに攻撃し、攻撃アニメーションが終了するとプレイヤーの追跡ステートに切り替わります。

```cpp
//ファイル：AttackPlayerBT.cpp

EBTNodeResult::Type UAttackPlayerBT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bIsAttackEnd = false;

	//敵の取得
	AEnemyBase* Enemy = GetEnemy(OwnerComp);

	if (Enemy == nullptr) 	return EBTNodeResult::Failed;
	if (Enemy->AttackAnimMontage == nullptr) 	return EBTNodeResult::Failed;

	//Playerの取得
	APawn* Player =  GetWorld()->GetFirstPlayerController()->GetPawn() ;
	if (Player == nullptr) 	return EBTNodeResult::Failed;

	//敵の向きをプレイヤーの方向に向ける
	FRotator NewRot = (Player->GetActorLocation() - Enemy->GetActorLocation()).Rotation();
	NewRot.Pitch = 0.0f;
	NewRot.Roll = 0.0f;
	Enemy->SetActorRotation(NewRot);

	//Enemyのところを示すUIを表示
	Enemy->SetEnemyDirectionIndicatorActive(true);

	//攻撃のアニメーションを再生
	float tmp_TimeCount = Enemy->PlayAnimMontage(Enemy->AttackAnimMontage);

	//攻撃のアニメーションの再生時間を取得
	tmp_TimeCount *= Enemy->AttackAnimMontage->RateScale;

	//攻撃のアニメーションの再生時間分、攻撃を行わないようにする
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(TimerHandle_AttackEnd, this, &UAttackPlayerBT::AttackEnd, tmp_TimeCount, false);

	return EBTNodeResult::InProgress;
}

void UAttackPlayerBT::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (bIsAttackEnd)	{
		//Stateをプレイヤーをプレイヤーに追跡のる状態に変更
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", (uint8)EEnemyState::Chase);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UAttackPlayerBT::AttackEnd()
{
	bIsAttackEnd = true;
}
```

### UIシステムのコード部分
UIシステムは、プレイヤーのステータス、敵の方向を示す矢印とHP、会話ウィンドウ、およびミニマップ（UEのプラグインを使用）の4つのコンポーネントから構成されています。

- **プレイヤーのステータス**
この部分では、プレイヤーのステータスを取得し、Blueprint側でデータを受け取る処理を行っています。
  
![Blackboardのスクリーンショット](Document/PlayerUI.png)

```cpp
//ファイル：DestinyChangerCharacter.h
//////////////////////////////////////////////////////////////////////////
//UI
	////UI Class
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UUserWidget* PlayerUI;

	//％を取得
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetHPPercent() { return HP / MaxHP; }

	//％を取得
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetGuardGaugePercent();
	float ADestinyChangerCharacter::GetAttackPower()
	{
		return MainWeapon->GetAttackPower() * fPower;
	}

	//攻撃力を取得
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetAttackPower();
	float ADestinyChangerCharacter::GetAttackPower()
	{
		return MainWeapon->GetAttackPower() * fPower;
	}

	//DestinySystemの残り時間を取得
	UFUNCTION(BlueprintCallable, Category = "UI")
		float GetDestinySystemTime();
	float ADestinyChangerCharacter::GetDestinySystemTime()
	{
		return GetWorld()->GetTimerManager().GetTimerRemaining(DestinySystemTimerHandle);
	}

	//Get Level Exp LevelUpExp Tuprle
	UFUNCTION(BlueprintCallable, Category = "UI")
		FLevelData GetLevelData() { return LevelData; }
```

- **敵の方向を示す矢印とHP**

この部分では、敵の方向を赤い矢印でUI上に表示し、敵がプレイヤーに追跡する際に矢印が表示されます。また、敵のHPはプレイヤーに攻撃された際にのみ表示されます。

- **敵の方向を示す矢印**

![Blackboardのスクリーンショット](Document/EnemyTargeting.png)
  
```cpp
//ファイル：EnemyTargeting.cpp
void UEnemyTargeting::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Enemy == nullptr || PlayerArrow == nullptr) {
		RemoveFromParent();	//敵とプレイヤーがいないなら削除
		return;
	}

	FRotator Rotator = GetLookAtRotationYaw();
	TargetingImage->SetRenderTransformAngle(Rotator.Yaw);	//敵の向きとプレイヤーの方向の差分を取得し、UIの角度を変更する
}

void UEnemyTargeting::Init(AActor* _Enemy, UArrowComponent* _PlayerArrow)
{
	Enemy = _Enemy;
	PlayerArrow = _PlayerArrow;
}

FRotator UEnemyTargeting::GetLookAtRotationYaw()
{
	if (Enemy == nullptr || PlayerArrow == nullptr) {
		RemoveFromParent();
		return FRotator();
	}

	FVector Start = Enemy->GetRootComponent()->GetComponentLocation();									//敵の位置
	FVector End = PlayerArrow->GetComponentLocation();		//プレイヤーの位置

	FVector Direction = End - Start;		//プレイヤーの位置から敵の位置を引く
	Direction *= -1;						//反転

	Direction.Normalize(0.0001);
	float EnemyYaw = Direction.Rotation().Yaw;			// 

	//-------------------------------Player-----------------------------------------
	auto tmp = PlayerArrow->GetForwardVector();
	tmp.Normalize(0.0001);
	float PlayerYaw = tmp.Rotation().Yaw;

	return FRotator(0, EnemyYaw - PlayerYaw, 0); //敵の向きとプレイヤーの方向の差分を返す
}

```

- **敵のHP　UI**
  
```cpp
//ファイル：Base_WidgetComponent.cpp
void UBase_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	//ワールドで表示する
	SetWidgetSpace(EWidgetSpace::World);	
	if (WidgetClass != nullptr)	{
		SetWidgetClass(WidgetClass);	//BP側で設定したWidgetClassをセット
	}

	SetVisibility(false);	//最初は非表示
	
}

void UBase_WidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LookAtPlayer();
}

//向きをプレイヤーに向ける
void UBase_WidgetComponent::LookAtPlayer()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		//Get camera location
		APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
		if (CameraManager == nullptr) return;

		UCameraComponent* CameraComponent = Cast<UCameraComponent>(CameraManager->GetViewTarget()->GetComponentByClass(UCameraComponent::StaticClass()));
		if (CameraComponent == nullptr) return;

		FVector CameraLocation = CameraComponent->GetComponentLocation();
		//Look at camera
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), CameraLocation);

		//ReSet rotation
		LookAtRotation.Pitch = 0.0f;
		LookAtRotation.Roll = 0.0f;

		//Apply rotation
		SetWorldRotation(LookAtRotation);
	}
}

void UBase_WidgetComponent::ShowHPUI(float _time)
{
	//Component のActorを取得
	AActor* Owner = GetOwner();

	//Widgetを表示
	SetVisibility(true);

	Owner->GetWorldTimerManager().SetTimer(ShowUITimerHandle, this, &UBase_WidgetComponent::HideHPUI, _time, false);

}

void UBase_WidgetComponent::HideHPUI()
{
	//Component のActorを取得
	AActor* Owner = GetOwner();

	SetVisibility(false);

	Owner->GetWorldTimerManager().ClearTimer(ShowUITimerHandle);
}

void UBase_WidgetComponent::SetHPInfo(float HP, float MaxHP)
{
	if (WidgetClass != nullptr) {
		//Get Character Widget
		UCharacterBase_UMG* CharacterWidget = Cast<UCharacterBase_UMG>(GetWidget());
		if (CharacterWidget != nullptr) {
			//Set HP
			CharacterWidget->SetPlayerInfo(HP, MaxHP);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("CharacterWidget is nullptr"));
		}
	}
}
```

- **会話ウィンドウ**
このコンポーネントでは、話す人の名前と会話内容を設定する処理を行っています。

![Blackboardのスクリーンショット](Document/QuestSpeaker.png)

```cpp
//ファイル：Dialogue_UMG.h

UCLASS()
class DESTINYCHANGER_API UDialogue_UMG : public UUserWidget
{
	GENERATED_BODY()

public:
	//virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* Canvas;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* SpeakerName;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* DialogueText;

	//ぼかし
	UPROPERTY(Meta = (BindWidget))
		class UBackgroundBlur* Blur;
	UPROPERTY(Meta = (BindWidget))
		class UBackgroundBlur* BlurName;



	//Set SpeakerName
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void SetSpeakerName(FText Name);

	//Set DialogueText
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void SetDialogueText(FText Text);
	
};

void UDialogue_UMG::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDialogue_UMG::SetSpeakerName(FText Name)
{
	SpeakerName->SetText(Name);
}

void UDialogue_UMG::SetDialogueText(FText Text)
{
	DialogueText->SetText(Text);
}


```

### 会話システムのコード部分
この部分では、DialogueNodeの構造では、話す人の名前と話す内容となっております。DialogueManagerコンポーネントが配列のDialogueNodeを使用して、会話の内容をＵＩに送り込む。そして、デリゲートを使って関数ポインタを保存して、会話が終了の時に何か（Destoryとか）のメソッドを呼び出し。

```cpp
//ファイル：DialogueManager.h/cpp

//会話の構造
USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		FText SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		FText DialogueText;
};
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		TArray<FDialogueNode> DialogueData; // 会話データ

	//Flag
	bool bIsDialogueActive; // 会話がアクティブかどうか

public:
	//入口
	void EnterDialogue(AActor* _actor = nullptr); // 会話に入る

	//GetFlag
	bool GetIsDialogueActive() const { return bIsDialogueActive; } // 会話がアクティブかどうかを取得する
		
//////////////////////////////////////////////////////////////////////////
//Delegate
public:
	DialogueFinishedDelegate DialogueFinished; // 会話が終わった時のデリゲート

	template <typename ObjectType, typename MethodType>
	void AddDialogueFinishedEventCall(ObjectType* Object, MethodType Method)
	{
		DialogueFinished.AddUObject(Object, Method);
	}



/**
 * 会話を開始します。
 */
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

/**
 * 現在のダイアログがあるかどうかを返します。
 *
 * @return ダイアログの有無
 */
bool UDialogueManager::HasDialogueToDisplay() const
{
	return DialogueData.IsValidIndex(CurrentDialogueIndex);
}

/**
 * 現在の会話の次のノードを表示します。
 */
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

		//　会話が終わったらDelegateを呼び出す
		if (DialogueFinished.IsBound())		{
			DialogueFinished.Broadcast();
		}

	}
}

/**
 * 現在の(次の)ダイアログの説明を返します。
 *
 * @return 現在の(次の)ダイアログの説明
 */
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

/**
 * キャラクターが会話に入った場合、
 * そのキャラクターがUInteractComponentを持っている場合は、UIの表示を隠します。
 *
 * @param _Caller キャラクターのアクターオブジェクト
 */
void UDialogueManager::EnterDialogue(AActor* _Caller)
{

	if (_Caller != nullptr) {
		_Caller->FindComponentByClass<UInteractComponent>()->SetUIActive(!bIsDialogueActive);
	}

	if (!bIsDialogueActive) {
		StartDialogue();
	}
	else {
		ShowNextDialogue();
	}

}
```

### クエストシステムのコード部分
クエストシステムは、プレイヤーに追加された`QuestSystem`コンポーネント、`QuestActorInterface`を継承したActor、そして`ItemGiverComponent`および`QuestGiverComponent`で構成されています。

- **QuestSystemコンポーネント**:
  こちらはクエストの構造やクエストクラスの管理を行うコンポーネントです。

- **QuestActorInterfaceを継承したActor**:
  このActorはクエストが達成された時に、次のクエストをアクティブにできるクラスです。

- **ItemGiverComponentおよびQuestGiverComponent**:
  `ItemGiverComponent`はアイテムをプレイヤーのバッグに与えるクラスで、`QuestGiverComponent`はプレイヤーの`GameSystem`コンポーネントにクエストを追加するクラスです。

内容が多いため、以下では`QuestSystem`コンポーネントのみを紹介します。


```cpp
//ファイル：QuestSystem.h

DECLARE_DELEGATE_OneParam(NotifyExecutingQuest, FName);
DECLARE_DELEGATE_OneParam(NotifyExecutingQuestComplete, FName);//クエストが完了した時に呼び出すデリゲート

//クエストの会話
USTRUCT(BlueprintType)
struct FQuestDialogue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエスト受注時の会話
	FText AcceptDialogue;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエスト提出時の会話
	FText SubmitDialogue;		
};

//クエストの種類
UENUM(BlueprintType)
enum class EQuestType : uint8
{
	DefeatEnemy UMETA(DisplayName = "DefeatEnemy"),	//敵を倒す
	CollectItem UMETA(DisplayName = "CollectItem"),	//アイテムを集める
	TalkToNPC UMETA(DisplayName = "TalkToNPC")		//NPCと会話する
};


//クエストの詳細
USTRUCT(BlueprintType)
struct FQuestDetail
{
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストID
		FName ID;				

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//報酬経験値
		int32 RewardExp;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//報酬アイテム
		TMap<FName, int32> RewardItems;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストの説明
		FText Description;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストの種類
		EQuestType QuestType;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//必要な数
		int32 NeedNum;			

	UPROPERTY(EditAnywhere, BlueprintReadWrite) //必要なターゲットID
		FName NeedTargetID;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//提出するターゲットID
		FName SubmitTargetID;	
};

//クエストの構造
USTRUCT(BlueprintType)
struct FQuestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエスト名
		FText QuestName;				

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエスト内容
		FText QuestContent;				

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストの簡単な説明
		FText ShortDescription;			

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストの詳細
		FQuestDetail QuestDetail;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストの会話
		FQuestDialogue QuestDialogue;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)	//クエストを受注するための条件
		FName ActiveCondition;			
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DESTINYCHANGER_API UQuestSystem : public UActorComponent
{
	GENERATED_BODY()

	//GetPlayer
	class ADestinyChangerCharacter* GetPlayer();

protected:
	//アクティブなクエスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> ActiveQuests;
	//クリアしたクエスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> CompletedQuests;
	//実行中のクエスト
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FName> ExecutingQuests;
	//クエストアイテム
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<FName, int32> QuestItems;
	//敵を倒した記録
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<FName, int32> DefeatRecords;

////////////////////////////////////////////////////////////////////////////////////
public:
	//　受注可能なクエストを追加する
	UFUNCTION(BlueprintCallable)
		void AddActiveQuest(FName QuestID);

	//　クエストをクリアする
	UFUNCTION(BlueprintCallable)
		void AddCompletedQuest(FName QuestID);

	//　実行中のクエストを追加する
	UFUNCTION(BlueprintCallable)
		void AddExecutingQuest(FName QuestID);

	//　クエストアイテムを追加する
	UFUNCTION(BlueprintCallable)
		void AddQuestItem(FName ItemID, int32 Num);

	//　敵を倒した記録を追加する
	UFUNCTION(BlueprintCallable)
		void AddDefeatRecord(FName EnemyID, int32 Num);

	template <typename ObjectType, typename MethodType>
	void BindUINotifyExecutingQuest(ObjectType* Object, MethodType Method)
	{
		UINotifyExecutingQuest.BindUObject(Object, Method);
	}

	//実行中のクエストを完了したことを通知
	NotifyExecutingQuestComplete NotifyExecutingQuestComplete;

	template <typename ObjectType, typename MethodType>
	void BindNotifyExecutingQuestComplete(ObjectType* Object, MethodType Method)
	{
		NotifyExecutingQuestComplete.BindUObject(Object, Method);
	}

	//クエストをコンプリートした後の処理
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
		void CompleteQuest(FName QuestID);
};

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
	//QuestDatabaseからクエストが存在するか確認する
	if( !GetGameMode()->GetQuestDatabase()->QuestExists(QuestID) ) return;

	//アクティブのクエストを追加する
	ActiveQuests.Add(QuestID);

	//実行中のクエストに追加する
	AddExecutingQuest(QuestID);
}

void UQuestSystem::AddCompletedQuest(FName QuestID)
{
	//完成のクエストを追加する
	CompletedQuests.Add(QuestID);

	//アクティブのクエストから削除する
	ActiveQuests.Remove(QuestID);

	//実行中のクエストから削除する
	ExecutingQuests.Remove(QuestID);

	//Print
	UE_LOG(LogTemp, Warning, TEXT("Completed Quest: %s"), *QuestID.ToString());

	//クエストを完成したことを通知する
	NotifyExecutingQuestComplete.ExecuteIfBound(QuestID);

	//Expを追加する
	GetGameMode()->AddExp( GetGameMode()->GetQuestDatabase()->GetQuest(QuestID).QuestDetail.RewardExp );
}

void UQuestSystem::AddExecutingQuest(FName QuestID)
{
	//実行中のクエストを追加する
	ExecutingQuests.Add(QuestID);

	//実行中のクエストを追加したことを通知する
	UINotifyExecutingQuest.ExecuteIfBound(QuestID);

}

void UQuestSystem::AddQuestItem(FName ItemID, int32 Num)
{
	//ItemBaseからアイテムが存在するか確認する
	if (!GetGameMode()->GetItemDatabase()->ItemExists(ItemID)) return;

	//QuestItemsにアイテムを追加する
	QuestItems.Add(ItemID, QuestItems.FindRef( ItemID ) + Num);

	//アイテムの数がクエストの数を超えたら、クエストを完成する。
	//そのため、全てのクエストを確認する
	for (auto& QuestID : ExecutingQuests) {
		//QuestDatabaseからクエストを取得する
		FQuestStruct Quest = GetGameMode()->GetQuestDatabase()->GetQuest(QuestID);

		//クエストのアイテムがQuestItemsに存在するか確認する
		if (Quest.QuestDetail.NeedNum > 0) {

			int32 tmp_NowNum = QuestItems.FindRef(Quest.QuestDetail.NeedTargetID);
			int32 tmp_NeedNum = Quest.QuestDetail.NeedNum;
			//クエストのアイテムの数がQuestItemsの数を超えたら、クエストを完成する
			if (tmp_NowNum >= tmp_NeedNum){
				AddCompletedQuest(QuestID);
			}
		}
	}
}

TArray<FQuestStruct> UQuestSystem::GetActiveQuests()
{	
	//QuestDatabaseからアクティブクエストを取得する
	TArray<FQuestStruct> Quests;
	for (auto& QuestID : ActiveQuests) {
		Quests.Add(GetGameMode()->GetQuestDatabase()->GetQuest(QuestID));
	}
	return Quests;
}

TArray<FQuestStruct> UQuestSystem::GetCompletedQuests()
{
	//QuestDatabaseから完成クエストを取得する
	TArray<FQuestStruct> Quests;
	for (auto& QuestID : CompletedQuests) {
		Quests.Add(GetGameMode()->GetQuestDatabase()->GetQuest(QuestID));
	}
	return Quests;
}

TArray<FQuestStruct> UQuestSystem::GetExecutingQuests()
{
	//QuestDatabaseから実行中クエストを取得する
	TArray<FQuestStruct> Quests;
	for (auto& QuestID : ExecutingQuests) {
		Quests.Add(GetGameMode()->GetQuestDatabase()->GetQuest(QuestID));
	}
	return Quests;
}

int32 UQuestSystem::GetQuestItems(FName ItemID)
{
	//QuestItems からアイテムの数を取得する
	return QuestItems.FindRef(ItemID);
}

int32 UQuestSystem::GetDefeatRecords(FName ItemID)
{
	//DefeatRecords から敵の数を取得する
	return DefeatRecords.FindRef(ItemID);
}

```

## 5. 自分の役割と貢献
このプロジェクトは個人で開発されました。設計、プログラミング、テスト、およびデバッグの全てのフェーズを担当しました。このプロジェクトを通じて、自分自身の技術的能力を向上させ、独立してタスクを完了する能力を強化しました。


## 6. 成果と学び
このプロジェクトを通じて、アクションゲームにおける爽快感の作り方について少し理解することができました。また、Unreal Engine (UE) でのコンポーネント開発の基本的な設計にも触れることができました。最も重要な成果は、3D RPGゲームの基本構造を把握することができた点です。元々の目標はRPGの制作方法について学ぶことでしたので、このゲーム制作を通じて、敵AIの設計、UIの作成方法、アニメーションNotifyの使用方法など多くのことを学べました。さらに、UEの基本機能に一定の不満を感じ、`AnimNotifyState_TimedParticleEffect`クラスでは一度に1つのParticleEffectしか生成できないため、UEのソースコードを調査し、メソッドをオーバーライドして親クラスのメソッドを呼ばずに一度に3つのParticleEffectを生成することができるようになりました。これにより、他人のコードを読む能力も向上しました。

他にも、3Dゲームにおける特定の時間で攻撃用のコリジョンを生成する方法や、ヒットストップとヒットエフェクトなどの機能を統合した`AttackAssistComponent`の設計方法も学びました。この技術は、同時に東京ゲームショーのプロジェクトに参加しているチームメンバーと共有しました。

この経験は、私にとって非常に価値のあるものであり、今後のゲーム開発のキャリアにおいて、このプロジェクトで学んだことが大いに役立つと確信しています。



## 7. ビジュアルとメディア
![スクリーンショット](Document/Title.png)  

### プレイ動画
[プロジェクトデモビデオ](https://youtu.be/-7P6c4o86i4)

## 8. プロジェクトのリンク
- [GitHubリポジトリ](https://github.com/yu-zuki/DestinyChanger)  
### 実行ファイルのダウンロード
- [実行可能なデモ Github](https://github.com/yu-zuki/DestinyChanger/releases/tag/Demov1.0)
- [実行可能なデモ GoogleDrive](https://drive.google.com/drive/folders/1w2h7GhYy8HUFfTIW6YDCepHEAFAgkzOj?usp=drive_link)

## 9. 連絡先情報
- 名前: トウ　ゼイキ
- メール: touzeiki@gmail.com
