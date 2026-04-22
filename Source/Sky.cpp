#include "Sky.h"
#include "../Engine/Direct3D.h"

Sky::Sky(GameObject* parent)
{
}

void Sky::Initialize()
{
	hModel_ = Model::Load("Model/Sky.fbx");
}

void Sky::Update()
{
}

void Sky::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, Direct3D::SHADER_SKY);
}

void Sky::Release()
{
}
