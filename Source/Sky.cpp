#include "Sky.h"
#include "../Engine/Direct3D.h"

Sky::Sky(GameObject* parent)
	:GameObject(parent, "Sky"), hModel_(-1)
{
}

void Sky::Initialize()
{
	hModel_ = Model::Load("Model/Stage/Sky.fbx");
	transform_.position_ = { 0.0f, -10.0f, 0.0f };
	transform_.scale_ = { 0.5f, 0.5f, 0.5f };
}

void Sky::Update()
{
}

void Sky::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, 0.0f);
}

void Sky::Release()
{
}
