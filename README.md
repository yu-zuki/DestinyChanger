# DestinyChanger

## 1. プロジェクトの概要
趣味でARPGを作ってみました！

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

### デスティニーシステム  
ディスティニーシステムは、プレイヤーが敵の攻撃をガードした際に、一時的にプレイヤーの攻撃力を増加させるシステムです。攻撃力の増加倍率は、時間の経過とともに徐々に減少します。また、このシステムの効果時間には上限が存在します。

このシステムは、プレイヤーが戦略的なガードを成功させた際に、一時的な攻撃力のブーストを提供することで、ゲームプレイのダイナミクスを高める効果が期待されます。

[→ディスティニーシステムのコードを参照](#ディスティニーシステムに関連する主要なコードの部分です)

### エネミーシステム
さまざまな種類の敵キャラクターがゲーム内に登場します。それぞれに独自の攻撃パターンと戦略があります。（まだ1種類しか実装してません。）

[→エネミーシステムのコードを参照](#エネミーシステムのコード部分)

### UIシステム
ゲームの進行状況、キャラクターの状態、敵の位置や方向などの情報をプレイヤーに表示します。

[→UIシステムのコードを参照](#UIシステムのコード部分)

### 会話システム
NPCとの対話を通じて、ストーリーが進行します。

[→会話システムのコードを参照](#会話システムのコード部分)

### アイテムシステム
プレイヤーはゲーム内でアイテムを探すことで、クエストの進捗を達成できます。

[→アイテムシステムのコードを参照](#アイテムシステムのコード部分)

### クエストシステム
クエストを通じて、プレイヤーはゲーム内のミッションを完了することができます。

[→クエストシステムのコードを参照](#クエストシステムのコード部分)

（各モジュールの説明写真）
![スクリーンショット](screenshot_url.png)  


## 4. ソースコードの説明とサンプル
このセクションでは、重要なコードスニペットやアルゴリズムを共有し、それらが何を実現するのか、なぜそれが重要で効率的なのかを説明します。
### バトルシステムのコード部分
```cpp

```

### ディスティニーシステムに関連する主要なコードの部分です。

```cpp
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
```cpp

```

### UIシステムのコード部分
```cpp

```

### 会話システムのコード部分
```cpp

```

### アイテムシステムのコード部分
```cpp

```

### クエストシステムのコード部分
```cpp

```

## 5. 自分の役割と貢献
このプロジェクトは個人で開発されました。設計、プログラミング、テスト、およびデバッグの全てのフェーズを担当しました。このプロジェクトを通じて、自分自身の技術的能力を向上させ、独立してタスクを完了する能力を強化しました。


## 6. 成果と学び
このセクションでは、プロジェクトを通じて得られた成果や学びを共有します。

## 7. ビジュアルとメディア
![スクリーンショット](screenshot_url.png)  
[プロジェクトデモビデオ](video_url)

## 8. プロジェクトのリンク
- [GitHubリポジトリ](https://github.com/your-username/project-repo)  
- [実行可能なデモ](https://demo_url)

## 9. 連絡先情報
- 名前: トウ　ゼイキ
- メール: touzeiki@gmail.com
