#include "TitleUI.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"

TitleUI::TitleUI(GameObject* parent)
	:GameObject(parent, "TitleUI"), hModel_(-1)
{
}

void TitleUI::Initialize()
{
	//モデルのロード
	hModel_ = Model::Load("Model/Ground.fbx");
	assert(hModel_ >= 0);
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
}

void TitleUI::Update()
{
}

void TitleUI::Draw()
{
	//描画
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TitleUI::Release()
{
}
