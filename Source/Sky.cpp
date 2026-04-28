#include "Sky.h"
#include "../Engine/Direct3D.h"

Sky::Sky(GameObject* parent)
	:GameObject(parent, "Sky"), hModel_(-1)
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
	Direct3D::SetShader(Direct3D::SHADER_SKY);

	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Sky::Release()
{
}
