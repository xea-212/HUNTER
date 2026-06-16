#pragma once
#include "../Engine/GameObject.h"
#include "Animator.h"

enum PlayerState
{
	PLAYER_STATE_FREE,
	PLAYER_STATE_ATTACK_MAIN,
	PLAYER_STATE_ATTACK_SUB,
};

enum PlayerParameter
{
	PLAYER_POSITION = 1,
	PLAYER_ROTATE,
	PLAYER_SCALE,
	PLAYER_HP,
	PLAYER_POWER,
	PLAYER_SPEED,
	PLAYER_VELOCITY,
	PLAYER_GRAVITY,
};

enum PlayerAnimID
{
	ANIM_IDLE = 0,
	ANIM_WALK,
	ANIM_RUN,
	ANIM_ATTACK_MAIN,
	ANIM_ATTACK_SUB,
};

enum column
{
	COLUMN_POSITION_X = 1,
	COLUMN_POSITION_Y,
	COLUMN_POSITION_Z,
	COLUMN_ROTATE_X = 1,
	COLUMN_ROTATE_Y,
	COLUMN_ROTATE_Z,
	COLUMN_SCALE_X = 1,
	COLUMN_SCALE_Y,
	COLUMN_SCALE_Z,
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

	Transform GetTransform() { return transform_; } // プレイヤーのTransformを取得
	int GetHP() { return param_.hp_; } // 体力を取得
	int GetMaxHP() { return maxHP; } // 最大体力を取得
	int GetPower() { return param_.power_; } // 攻撃力を取得
	int Damage(int damage) { param_.hp_ -= damage; return param_.hp_; } // ダメージを受ける（体力を減らす）関数。引数はダメージ量。戻り値は現在の体力。
	int Heal(int heal) { param_.hp_ += heal; return param_.hp_; } // 回復する（体力を増やす）関数。引数は回復量。戻り値は現在の体力。

	XMFLOAT3 GetPosition() { return transform_.position_; } // プレイヤーの位置を取得
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
	int maxHP; // プレイヤーの最大体力

	Animator* animator; // アニメーター
	
	XMVECTOR vPos; // プレイヤーの位置

	bool isRun; // プレイヤーが走っているかどうか
	bool isAttack; // プレイヤーが攻撃しているかどうか
};