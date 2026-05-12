#pragma once
#include "../Engine/GameObject.h"
#include <vector>

struct StageData
{
	std::string modelName;

	XMFLOAT3 position;
	XMFLOAT3 rotate;
	XMFLOAT3 scale;
};

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

class StageManager
{
public:
	StageManager();
	~StageManager();
	void Initialize();
private:
	void LoadStageData(std::string fileName);
	std::vector<StageData>& stageData_;
};