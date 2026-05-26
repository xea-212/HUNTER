#pragma once
#include "../Engine/GameObject.h"
#include <vector>

enum AnimationParam
{
	ANIMATION_FILENAME = 0,
	ANIMATION_START,
	ANIMATION_END,
	ANIMATION_SPEED,
	ANIMATION_LOOP,
};

enum PlayerAnimID
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

	void SetModel(int model) { model_ = model; }
	void AttachAnimation(std::string fileName); // CSVファイルからアニメーションデータを読み込む
	void Play(int ID, float speed = 1.0f); // アニメーションを再生
private:
	struct AnimationData
	{
		std::string fileName_; // アニメーションのファイル名
		int startFrame_; // アニメーションの開始フレーム
		int endFrame_; // アニメーションの終了フレーム
		float speed_; // アニメーションの再生速度
		bool loop_; // アニメーションをループさせるかどうか
	};
	std::vector<AnimationData> anim_;
	int model_;
	int currentAnim_;
	float speed_;
	bool isPlay_;
};