#pragma once
#include "../Engine/GameObject.h"
#include "StageManager.h"
#include <vector>

class StageObject : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（Stage）
	StageObject(GameObject* parent, std::vector<StageData>& stageData);
	//描画
	void Initialize() override;
	void Draw() override;
	void Update() override;
	void Release() override;
private:
	int hModel_;
	std::vector<StageData>& stageData_;
};