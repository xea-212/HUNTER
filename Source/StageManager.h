#pragma once
#include "../Engine/GameObject.h"
#include <vector>

// ステージのデータ構造
struct StageData
{
	std::string modelName;

	XMFLOAT3 position;
	XMFLOAT3 rotate;
	XMFLOAT3 scale;
};

// CSVファイルの列番号
enum STAGE_DATA
{
	STAGE_DATA_MODELNAME = 0,
	STAGE_DATA_POSX,
	STAGE_DATA_POSY,
	STAGE_DATA_POSZ,
	STAGE_DATA_ROTX,
	STAGE_DATA_ROTY,
	STAGE_DATA_ROTZ,
	STAGE_DATA_SCAX,
	STAGE_DATA_SCAY,
	STAGE_DATA_SCAZ,
};

// ステージの管理を行うクラス
class StageManager : public GameObject
{
public:
	StageManager(GameObject* parent);
	~StageManager();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void LoadStageData(std::string fileName); // CSVファイルからステージデータを読み込む
	void CreateStageObject(); // ステージオブジェクトを生成する
private:
	std::vector<StageData>& stageData_;
};