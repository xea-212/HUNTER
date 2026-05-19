#pragma once
#include "../Engine/GameObject.h"

enum PlayerState
{
	PLAYER_STATE_FREE,
	PLAYER_STATE_ATTACK_MAIN,
	PLAYER_STATE_ATTACK_SUB,
};

enum PlayerParameter
{
	PLAYER_HP = 1,
	PLAYER_POWER,
	PLAYER_SPEED,
	PLAYER_VELOCITY,
	PLAYER_GRAVITY,
};

class Player : public GameObject
{
public:
	//コンストラクタ
	Player(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;

	// パラメーターの読み込み
	void SetParameter(std::string fileName);

	void Free();
	//攻撃
	void Attack();

	int GetHP() { return param_.hp_; } // 体力を取得
	int GetPower() { return param_.power_; } // 攻撃力を取得
	int Damage(int damage) { param_.hp_ -= damage; return param_.hp_; } // ダメージを受ける（体力を減らす）関数。引数はダメージ量。戻り値は現在の体力。
	int Heal(int heal) { param_.hp_ += heal; return param_.hp_; } // 回復する（体力を増やす）関数。引数は回復量。戻り値は現在の体力。
private:
	int hModel_; // モデルのハンドル
	PlayerState state; // プレイヤーの状態
	
	struct PlayerParam{
		int hp_; // 体力
		int power_; // 攻撃力
		float speed_; // 移動速度

		float gravity_; // 重力の強さ
		XMVECTOR velocity_; // 速度
	};
	PlayerParam param_; // プレイヤーのパラメーター
	
	XMVECTOR vPos;
};