#pragma once
#include "UI.h"
#include "Player.h"
#include "../Engine/Sprite.h"

class HpBar : public UI
{
public:
	//コンストラクタ
	HpBar(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
private:
	Player* player_;
	Sprite* sprite_;

	int hp_;
	int maxHp_;

	float rate_;
};