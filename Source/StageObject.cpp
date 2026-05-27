#include "StageObject.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"


StageObject::StageObject(GameObject* parent)
	:GameObject(parent, "StageObject"), hModel_(-1)
{
}

void StageObject::Initialize()
{
	SetStageData(StageData());
}

void StageObject::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, 0.0f);
}

void StageObject::Update()
{

}

void StageObject::Release()
{
}

void StageObject::SetStageData(const StageData& data)
{
	hModel_ = Model::Load("Model/Stage/" + data.modelName + ".fbx");

	transform_.position_ = data.position;
	transform_.rotate_ = data.rotate;
	transform_.scale_ = data.scale;
}
