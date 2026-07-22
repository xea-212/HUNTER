#pragma once
#include "../Engine/GameObject.h"

class Loading : public GameObject
{
public:
	Loading();
	~Loading();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	bool isLoadEnd_;
};