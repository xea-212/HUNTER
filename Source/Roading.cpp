#include "Roading.h"
#include "../Engine/Model.h"

Roading::Roading()
{
}

Roading::~Roading()
{
}

void Roading::Initialize()
{
	Model::Load("Model/Character/Player.fbx");
	Model::Load("Model/Character/Enemy.fbx");
	Model::Load("Model/Stage/Ground.fbx");
	Model::Load("Model/Stage/Sky.fbx");
}

void Roading::Update()
{
}

void Roading::Draw()
{
}

void Roading::Release()
{
}
