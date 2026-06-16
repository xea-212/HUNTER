#pragma once
#include "../Engine/GameObject.h"
#include <vector>

class Animator : public GameObject
{
public:
	struct AnimationData
	{
		std::string fileName_; // アニメーションのファイル名
		float startFrame_; // アニメーションの開始フレーム
		float endFrame_; // アニメーションの終了フレーム
		float speed_; // アニメーションの速度
		bool loop_; // アニメーションをループさせるかどうか

		int animModel_; // アニメーションのモデルのハンドル
	};

	enum ANIMATION_DATA
	{
		ANIMATION_DATA_FILENAME = 0,
		ANIMATION_DATA_STARTTIME,
		ANIMATION_DATA_ENDTIME,
		ANIMATION_DATA_SPEED,
		ANIMATION_DATA_LOOP,
	};

	Animator(GameObject* parent);
	~Animator();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void AttachAnimation(std::string fileName); // アニメーションを追加する関数
	void Play(int ID, float speed = 1.0f); // アニメーションを再生する関数
	void Stop(); // アニメーションを停止する関数
	int GetAnimHandle(); // 現在再生中のアニメーションのモデルのハンドルを取得する関数
	bool IsPlaying(); // アニメーションが再生中かどうかを取得する関数

	float GetFrame(); // 現在のアニメーションの再生フレームを取得する関数
private:
	std::vector<AnimationData> anim_; // アニメーションデータのリスト

	int currentAnim_; // 現在再生中のアニメーションのID

	bool isPlay_; // アニメーションが再生中かどうか

	float frame_; // アニメーションの再生時間
	float speed_; // アニメーションの再生速度
};