#include "EnemyBullet.h"
#include "../Engine/Model.h"

EnemyBullet::EnemyBullet(GameObject* parent)
	:GameObject(parent, "EnemyBullet"), hModel_(-1), dirX_(0.0f), dirY_(0.0f), dirZ_(0.0f), speed_(0.0f)
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Initialize()
{
	hModel_ = Model::Load("Model/Character/Bullet.fbx");
}

void EnemyBullet::Update()
{
	const float gravity = 0.01f;

	dirY_ -= gravity;

	transform_.position_.x += dirX_ * speed_;
	transform_.position_.y += dirY_ * speed_;
	transform_.position_.z += dirZ_ * speed_;

	if (transform_.position_.y < 0.0f) {
		KillMe();
	}
}

void EnemyBullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void EnemyBullet::Release()
{
}

void EnemyBullet::Shot(XMFLOAT3 enemyPos, XMFLOAT3 playerPos)
{
	transform_.position_ = enemyPos;

	// 発射位置を少し上げる
	transform_.position_.y += 10.0f;

	float dx = playerPos.x - transform_.position_.x;
	float dz = playerPos.z - transform_.position_.z;

	float length = sqrtf(dx * dx + dz * dz);

	constexpr float minDistance = 0.001f;
	if (length <= minDistance) {
		return;
	}

	dirX_ = dx / length;

	// 最初は上方向へ飛ばす
	dirY_ = 0.5f;

	dirZ_ = dz / length;

	speed_ = 1.0f;
}