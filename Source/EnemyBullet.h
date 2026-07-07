#pragma once
#include "../Engine/GameObject.h"

class EnemyBullet : public GameObject
{
public:
	EnemyBullet(GameObject* parent);
	~EnemyBullet();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Shot(XMFLOAT3 enemyPos, XMFLOAT3 playerPos);
private:
	int hModel_;

	float dirX_;
	float dirY_;
	float dirZ_;

	float speed_;
};
