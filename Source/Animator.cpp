#include "Animator.h"
#include "../Engine/CsvReader.h"
#include "../Engine/Model.h"

Animator::Animator(GameObject* parent)
	:GameObject(parent, "Animator"), anim_{}, model_(-1), currentAnim_(-1), isPlay_(false)
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
		data.fileName_ = csv->GetString(line, ANIMATION_FILENAME);
		data.startFrame_ = csv->GetInt(line, ANIMATION_START);
		data.endFrame_ = csv->GetInt(line, ANIMATION_END);
		data.speed_ = csv->GetFloat(line, ANIMATION_SPEED);
		data.loop_ = csv->GetInt(line, ANIMATION_LOOP);
		anim_.push_back(data);
	}
}

void Animator::Play(int ID, float speed)
{
	if (ID < 0 || ID >= anim_.size() || currentAnim_ == ID)
		return;

	currentAnim_ = ID;
	speed_ = speed * anim_[ID].speed_;
	isPlay_ = true;

	Model::SetAnimFrame(model_, anim_[ID].startFrame_, anim_[ID].endFrame_, speed_, anim_[ID].loop_);
}
