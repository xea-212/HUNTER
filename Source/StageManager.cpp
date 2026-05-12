#include "StageManager.h"
#include "../Engine/CsvReader.h"

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
}

void StageManager::Initialize()
{
	
}

void StageManager::LoadStageData(std::string fileName)
{
	std::string path = "Assets/Data/";
	CsvReader* csv = new CsvReader(path + fileName + ".csv");
	for (int line = 0; line < csv->GetLines(); line++) {
		StageData data;
		data.modelName = csv->GetString(line, STAGE_DATA_MODELNAME);
		data.position.x = csv->GetFloat(line, STAGE_DATA_POSX);
		data.position.y = csv->GetFloat(line, STAGE_DATA_POSY);
		data.position.z = csv->GetFloat(line, STAGE_DATA_POSZ);
		data.rotate.x = csv->GetFloat(line, STAGE_DATA_ROTX);
		data.rotate.y = csv->GetFloat(line, STAGE_DATA_ROTY);
		data.rotate.z = csv->GetFloat(line, STAGE_DATA_ROTZ);
		data.scale.x = csv->GetFloat(line, STAGE_DATA_SCAX);
		data.scale.y = csv->GetFloat(line, STAGE_DATA_SCAY);
		data.scale.z = csv->GetFloat(line, STAGE_DATA_SCAZ);
		stageData_.push_back(data);
	}
	delete csv;
}
