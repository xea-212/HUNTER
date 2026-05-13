#pragma once
#include "../Engine/GameObject.h"

enum PlayerState
{
	PLAYER_STATE_IDLE,
	PLAYER_STATE_WALK,
	PLAYER_STATE_JUMP,
	PLAYER_STATE_ATTACK,
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

	int GetHP() { return hp_; }
	int GetPower() { return power_; }
	int Damage(int damage) { hp_ -= damage; return hp_; }
	int Heal(int heal) { hp_ += heal; return hp_; }
private:
	int hModel_;
	PlayerState state;
	struct {
		int hp_;
		int power_;
	};
	bool moveWork;
	bool moveRotate;
};