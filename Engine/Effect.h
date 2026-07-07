#pragma once
#include "Texture.h"

class Effect
{
public:
	Effect();
	~Effect();

	void Create(const char* filename, XMFLOAT3 pos, float lifetime, float size = 1.0f);

	void Update();
	void Draw();

	bool IsDead() const;

private:
	Texture texture_;

	XMFLOAT3 position_;

	float size_;

	float timer_;
	float life_;

	bool dead_;
};