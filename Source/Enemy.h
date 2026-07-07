#pragma once
#include "../Engine/GameObject.h"
#include "Animator.h"
#include "EnemyBullet.h"

enum EnemyState
{
	ENEMY_STATE_IDLE,
	ENEMY_STATE_FIND,
	ENEMY_STATE_CHASE,
	ENEMY_STATE_ATTACK,
	ENEMY_STATE_COOLDOWN,
	ENEMY_STATE_DAMAGE,
	ENEMY_STATE_SEARCH,
};

enum EnemyAnimID
{
	ENEMY_ANIM_IDLE = 1,
	ENEMY_ANIM_WALK,
	ENEMY_ANIM_JATTACK,
	ENEMY_ANIM_FLEX,
	ENEMY_ANIM_DRUN,
	ENEMY_ANIM_RUN,
	ENEMY_ANIM_ROAR,
	ENEMY_ANIM_SWIP
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

	void SetParameter(std::string fileName);
	void UpdatePlayerInfo();
	bool CanSeePlayer();

	void Idle();
	void Find();
	void Chase();
	void Attack();
	void Cooldown();
	void Damage();

	void SetSearchPos();
	void Search();
private:
	int hModel_;

	float dx_;
	float dz_;
	float dirX_;
	float dirZ_;
	float distance_;

	float attacktimer_;
	float chasetimer_;
	float cooltimer_; // クールダウン時間を管理する変数

	bool isFlex_;
	float flextimer_;

	EnemyState state;

	struct EnemyParam{
		int hp_;
		int power_;
		float speed_;

		float gravity_;
		XMVECTOR velocity_;
	};
	EnemyParam param_;

	int maxHP_;

	Animator* animator;

	EnemyBullet* eBullet;

	Transform pPos; // プレイヤーの位置を保存する変数

	int attackID_; // 攻撃アニメーションのID
	bool isAttack; // 攻撃中かどうかのフラグ
	bool isAttackSelect;
	bool isShot; // 弾を撃ったかどうかのフラグ

	XMFLOAT3 searchPos_;
	float searchTimer_;
};