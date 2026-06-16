#include "Animator.h"
#include "../Engine/Time.h"
#include "../Engine/CsvReader.h"
#include "../Engine/Model.h"

Animator::Animator(GameObject* parent)
	:GameObject(parent, "Animator"), currentAnim_(-1), isPlay_(false), frame_(0.0f), speed_(1.0f)
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

	if (!isPlay_ || currentAnim_ < 0) {
		return;
	}

	AnimationData& anim = anim_[currentAnim_];

	const float animFps = 30.0f; // アニメーションのフレームレート
	frame_ += animFps * Time::DeltaTime() * anim.speed_ * speed_;

	if(frame_ > anim.endFrame_) {
		if (anim.loop_ == 1) {
			frame_ = anim.startFrame_;
		} 
		else {
			frame_ = anim.endFrame_;
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
		data.startFrame_ = csv->GetFloat(line, ANIMATION_DATA_STARTTIME);
		data.endFrame_ = csv->GetFloat(line, ANIMATION_DATA_ENDTIME);
		data.speed_ = csv->GetFloat(line, ANIMATION_DATA_SPEED);
		data.loop_ = csv->GetInt(line, ANIMATION_DATA_LOOP);
		data.animModel_ = Model::Load(path + data.fileName_ + ".fbx");
		anim_.push_back(data);
	}
	delete csv;
}

void Animator::Play(int ID, float speed)
{
	if (ID < 0 || ID >= static_cast<int>(anim_.size())){
		return;
	}

	if (currentAnim_ == ID && isPlay_){
		return;
	}

	currentAnim_ = ID;
	speed_ = speed;
	frame_ = anim_[ID].startFrame_;
	isPlay_ = true;
}

void Animator::Stop()
{
	isPlay_ = false;
}

int Animator::GetAnimHandle()
{
	if (currentAnim_ < 0){
		return -1;
	}

	return anim_[currentAnim_].animModel_;
}

bool Animator::IsPlaying()
{
	return isPlay_;
}

float Animator::GetFrame()
{
	return frame_;
}
