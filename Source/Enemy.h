#pragma once
#include "../Engine/GameObject.h"
#include "Animator.h"

enum EnemyState
{
	ENEMY_STATE_FREE,
	ENEMY_STATE_ATTACK,
};

enum EnemyParameter
{
	ENEMY_HP = 1,
	ENEMY_POWER,
	ENEMY_SPEED,
};

enum EnemyAnimID
{
	ENEMY_ANIM_IDLE = 1,
	ENEMY_ANIM_WALK,
	ENEMY_ANIM_ATTACK,
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

	void Free();
	void Attack();
private:
	int hModel_;
	EnemyState state;

	struct EnemyParam{
		int hp_;
		int power_;
		float speed_;
	};
	EnemyParam param_;

	Animator* animator;
};