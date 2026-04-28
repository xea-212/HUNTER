#pragma once
#include "../Engine/GameObject.h"

enum EnemyState
{
	ENEMY_STATE_IDLE,
	ENEMY_STATE_WALK,
	ENEMY_STATE_JUMP,
	ENEMY_STATE_ATTACK,
};

class Enemy : public GameObject
{
public:
	//コンストラクタ
	Enemy(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
private:
	int hModel_;
	EnemyState state;
};