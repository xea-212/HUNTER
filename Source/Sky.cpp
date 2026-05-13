#include "Sky.h"
#include "../Engine/Direct3D.h"

Sky::Sky(GameObject* parent)
	:GameObject(parent, "Sky"), hModel_(-1)
{
}

void Sky::Initialize()
{
	hModel_ = Model::Load("Model/Ground.fbx");
}

void Sky::Update()
{
}

void Sky::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Sky::Release()
{
}
