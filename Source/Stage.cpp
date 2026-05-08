#include "Stage.h"
#include "../Engine/Direct3D.h"
#include "Sky.h"
#include "Player.h"
#include "Enemy.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), csv(nullptr)
{
}

void Stage::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);

	if (csv == nullptr) {
		csv = new CsvReader();
	}
	csv->Load("Data/StageObject.csv"); //CSVファイルの読み込み

	int height = csv->GetHeight(); //CSVファイルの行数を取得
	int width = csv->GetWidth();   //CSVファイルの列数を取得

	for (int i = 0; i < height; i++) {
		for (int i = 0; i < width; i++) {
			if (csv->GetString(i, 0) == "Stage") {
				StageData data;
				//モデル名
				data.modelName = csv->GetValue(i, MODEL_NAME);
				//位置
				data.position.x = csv->GetValue(i, POSITION_X);
				data.position.y = csv->GetValue(i, POSITION_Y);
				data.position.z = csv->GetValue(i, POSITION_Z);
				//回転
				data.rotate.x = csv->GetValue(i, ROTATE_X);
				data.rotate.y = csv->GetValue(i, ROTATE_Y);
				data.rotate.z = csv->GetValue(i, ROTATE_Z);
				//スケール
				data.scale.x = csv->GetValue(i, SCALE_X);
				data.scale.y = csv->GetValue(i, SCALE_Y);
				data.scale.z = csv->GetValue(i, SCALE_Z);
				stageData_.push_back(data);
			}
		}
	}
}
	

void Stage::Update()
{
}

void Stage::Draw()
{
	for (auto& obj : stageData_) {
		transform_.position_ = obj.position;
		transform_.rotate_ = obj.rotate;
		transform_.scale_ = obj.scale;

		Model::SetTransform(obj.modelName, transform_);
		Model::Draw(obj.modelName);
	}
}

void Stage::Release()
{
	if (csv != nullptr) {
		delete csv;
		csv = nullptr;
	}
}
