#pragma once
#include "../Engine/GameObject.h"

class UI : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	UI(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	virtual void Update() override{}
	//描画
	virtual void Draw() override{}
	//開放
	void Release() override;
};