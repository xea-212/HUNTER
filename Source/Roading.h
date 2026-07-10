#pragma once
#include "../Engine/GameObject.h"

class Roading : public GameObject
{
public:
	Roading();
	~Roading();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:

};