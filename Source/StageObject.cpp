#include "StageObject.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"


StageObject::StageObject(GameObject* parent)
	:GameObject(parent, "StageObject"), hModel_(-1)
{
}

void StageObject::Initialize()
{
	if (stageManager_ == nullptr){ 
		stageManager_ = new StageManager(stageData_);
	}
	stageManager_->LoadStageData("StageObject");
}

void StageObject::Draw()
{
	if (hModel_ != -1) {
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}
}

void StageObject::Update()
{

}

void StageObject::Release()
{
}

void StageObject::SetStageData(const StageData& data)
{
	hModel_ = Model::Load("Model/" + data.modelName + ".fbx");

	transform_.position_ = data.position;
	transform_.rotate_ = data.rotate;
	transform_.scale_ = data.scale;
}
