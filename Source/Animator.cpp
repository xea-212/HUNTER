#include "Animator.h"
#include "../Engine/Time.h"
#include "../Engine/CsvReader.h"

Animator::Animator(GameObject* parent)
	:GameObject(parent, "Animator"), model_(-1), currentAnim_(-1), isPlay_(false), time_(0.0f), speed_(1.0f)
{
}

Animator::~Animator()
{
}

void Animator::Initialize()
{
}

void Animator::Update()
{
	if (!isPlay_ || currentAnim_ < 0 || model_ < 0) {
		return;
	}

	AnimationData& anim = anim_[currentAnim_];

	time_ += Time::DeltaTime() * anim.speed_ * speed_;

	if(time_ > anim.endTime_) {
		if (anim.loop_) {
			time_ = anim.startTime_;
		} 
		else {
			time_ = anim.endTime_;
			isPlay_ = false;
		}
	}
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
		data.fileName_ = csv->GetString(line, ANIMATION_DATA_FILENAME);
		data.startTime_ = csv->GetFloat(line, ANIMATION_DATA_STARTTIME);
		data.endTime_ = csv->GetFloat(line, ANIMATION_DATA_ENDTIME);
		data.speed_ = csv->GetFloat(line, ANIMATION_DATA_SPEED);
		data.loop_ = csv->GetInt(line, ANIMATION_DATA_LOOP);
		anim_.push_back(data);
	}
	delete csv;
}

void Animator::Play(int ID, float speed)
{
	if (ID < 0 || ID >= anim_.size()) {
		return;
	}
	currentAnim_ = ID;
	speed_ = speed;
	time_ = anim_[ID].startTime_;
	isPlay_ = true;
}

void Animator::Stop()
{
	isPlay_ = false;
}

void Animator::SetModel(int hModel)
{
	model_ = hModel;
}

float Animator::GetTime()
{
	return time_;
}
