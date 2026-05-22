#include "Animator.h"
#include "../Engine/CsvReader.h"

Animator::Animator(GameObject* parent)
	:GameObject(parent, "Animator"), speed_(1.0f), anim_{}
{
}

void Animator::Initialize()
{
}

void Animator::Update()
{
}

void Animator::Draw()
{
}

void Animator::Release()
{
}

void Animator::AttachAnimation(std::string fileName)
{
	std::string path = "Anim/";
	CsvReader* csv = new CsvReader(path + fileName + ".csv");

	for (int line = 0; line < csv->GetLines(); line++) {
		AnimationData data;
		data.name_ = csv->GetString(line, ANIMATION_NAME);
		data.fileName_ = csv->GetString(line, ANIMATION_FILENAME);
		data.speed_ = csv->GetFloat(line, ANIMATION_SPEED);
		data.loop_ = csv->GetInt(line, ANIMATION_LOOP) != 0;
		anim_.push_back(data);
	}
}

void Animator::Play(int ID, float speed)
{
}
