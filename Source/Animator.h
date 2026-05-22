#pragma once
#include "../Engine/GameObject.h"
#include <vector>

enum AnimationParam
{
	ANIMATION_NAME = 0,
	ANIMATION_FILENAME,
	ANIMATION_SPEED,
	ANIMATION_LOOP,
};

enum AnimID
{
	ANIM_PLAYER_IDLE = 0,
	ANIM_PLAYER_WALK,
	ANIM_PLAYER_JUMP,
	ANIM_PLAYER_ATTACK,
	ANIM_ENEMY_IDLE,
	ANIM_ENEMY_WALK,
	ANIM_ENEMY_JUMP,
	ANIM_ENEMY_ATTACK
};

class Animator : public GameObject
{
public:
	Animator(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void AttachAnimation(std::string fileName); // CSVファイルからアニメーションデータを読み込む
	void Play(int ID, float speed); // アニメーションを再生
private:
	struct AnimationData
	{
		std::string name_; // アニメーションの名前
		std::string fileName_; // アニメーションのファイル名
		float speed_; // アニメーションの再生速度
		bool loop_; // アニメーションをループさせるかどうか
	};
	std::vector<AnimationData> anim_;
	int currentAnim_;
	float currentTime_;
	bool isPlay_;
	bool isLoop_;
};