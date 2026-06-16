#include "Enemy.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"
#include "Player.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), pPos{}, isAttack(false), distance(0.0f)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model/Character/Enemy.fbx");
	transform_.position_ = { 0.0f, 0.0f, 5.0f };
	transform_.rotate_ = { 0.0f, 180.0f, 0.0f };
	transform_.scale_ = { 0.1f, 0.1f, 0.1f };
	state = ENEMY_STATE_IDLE;

	animator = Instantiate<Animator>(this);
	animator->AttachAnimation("EnemyAnim");
	animator->Play(1); // 待機アニメーション
}

void Enemy::Update()
{
	switch (state) {
		case ENEMY_STATE_IDLE:
			Idle();
			break;
		case ENEMY_STATE_FIND:
			Find();
			break;
		case ENEMY_STATE_CHASE:
			Chase();
			break;
		case ENEMY_STATE_ATTACK:
			Attack();
			break;
		case ENEMYSTATE_COOLDOWN:
			Cooldown();
			break;
		case ENEMY_STATE_DAMAGE:
			Damage();
			break;
	}

	Player* player = (Player*)GetParent()->FindChildObject("Player");
	pPos = player->GetTransform();

	float dx = pPos.position_.x - transform_.position_.x;
	float dz = pPos.position_.z - transform_.position_.z;

	distance = sqrtf(dx * dx + dz * dz);
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, animator->GetAnimHandle(), animator->GetFrame());
}

void Enemy::Release()
{
}

void Enemy::Idle()
{
}

void Enemy::Find()
{
}

void Enemy::Chase()
{
}

void Enemy::Attack()
{
}

void Enemy::Cooldown()
{
}

void Enemy::Damage()
{
}
