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
	csv->Load("Data/StageObject.csv");

	int height = csv->GetHeight();
	int width = csv->GetWidth();

	for()
}

void Stage::Update()
{
}

void Stage::Draw()
{
}

void Stage::Release()
{
	if (csv != nullptr) {
		delete csv;
		csv = nullptr;
	}
}
