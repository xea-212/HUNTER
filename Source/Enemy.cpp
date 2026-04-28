#include "Enemy.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model/Enemy.fbx");
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
	Direct3D::SetShader(Direct3D::SHADER_3D);
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
