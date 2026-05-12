#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Model.h"
#include "../Engine/CsvReader.h"

struct StageData
{
	std::string modelName;
	int hModel_;

	XMFLOAT3 position;
	XMFLOAT3 rotate;
	XMFLOAT3 scale;
};

enum STAGE_DATA
{
	MODEL_NAME = 1,
	POSITION_X,
	POSITION_Y,
	POSITION_Z,
	ROTATE_X,
	ROTATE_Y,
	ROTATE_Z,
	SCALE_X,
	SCALE_Y,
	SCALE_Z
};

class Stage : public GameObject
{
public:
	//コンストラクタ
	Stage(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
private:
	int hModel_;
	CsvReader csv;
	std::vector<StageData> stageData_;
};