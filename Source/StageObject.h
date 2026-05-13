#pragma once
#include "../Engine/GameObject.h"
#include "StageManager.h"
#include <vector>

class StageManager;

class StageObject : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（Stage）
	StageObject(GameObject* parent);
	//描画
	void Initialize() override;
	void Draw() override;
	void Update() override;
	void Release() override;
	void SetStageData(const StageData& data);
private:
	int hModel_;
	std::vector<StageData> stageData_;
	StageManager* stageManager_;
};