#include "Enemy.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model/Character/Enemy.fbx");
	transform_.position_ = { 0.0f, 0.0f, 20.0f };
	transform_.rotate_ = { 0.0f, 180.0f, 0.0f };
	transform_.scale_ = { 0.1f, 0.1f, 0.1f };
	state = ENEMY_STATE_IDLE;
}

void Enemy::Update()
{
	switch (state) {
		case ENEMY_STATE_IDLE:
			break;
		case ENEMY_STATE_WALK:
			break;
		case ENEMY_STATE_JUMP:
			break;
		case ENEMY_STATE_ATTACK:
			break;
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
