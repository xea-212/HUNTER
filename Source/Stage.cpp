#include "../Engine/Direct3D.h"

#include "Stage.h"
#include "Sky.h"
#include "Player.h"
#include "Enemy.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hModel_(-1)
{
}

void Stage::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);

	csv.Load("Data/StageObject.csv"); //CSVファイルの読み込み

	int height = csv.GetHeight(); //CSVファイルの行数を取得
	int width = csv.GetWidth();   //CSVファイルの列数を取得

	for (int i = 0; i < height; i++)
	{
		if (csv.GetString(0, i) == "Stage")
		{
			StageData data;

			data.modelName = csv.GetString(MODEL_NAME, i);

			data.hModel_ = Model::Load("Model/" + data.modelName + ".fbx");

			data.position.x = csv.GetValue(POSITION_X, i);
			data.position.y = csv.GetValue(POSITION_Y, i);
			data.position.z = csv.GetValue(POSITION_Z, i);

			data.rotate.x = csv.GetValue(ROTATE_X, i);
			data.rotate.y = csv.GetValue(ROTATE_Y, i);
			data.rotate.z = csv.GetValue(ROTATE_Z, i);

			data.scale.x = csv.GetValue(SCALE_X, i);
			data.scale.y = csv.GetValue(SCALE_Y, i);
			data.scale.z = csv.GetValue(SCALE_Z, i);

			stageData_.push_back(data);

			OutputDebugStringA((std::to_string(data.hModel_) + "\n").c_str());
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

		Model::SetTransform(obj.hModel_, transform_);
		Model::Draw(obj.hModel_);
	}
}

void Stage::Release()
{
}
