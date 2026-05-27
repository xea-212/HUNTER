#pragma once
#include "../Engine/GameObject.h"
#include <vector>

class Animator : public GameObject
{
public:
	struct AnimationData
	{
		std::string fileName_; // アニメーションのファイル名
		float startTime_; // アニメーションの開始時間
		float endTime_; // アニメーションの終了時間
		float speed_; // アニメーションの速度
		bool loop_; // アニメーションをループさせるかどうか
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
	void SetModel(int hModel); // モデルのハンドルを設定する関数

	float GetTime(); // 現在のアニメーションの再生時間を取得する関数
private:
	std::vector<AnimationData> anim_; // アニメーションデータのリスト

	int model_; // モデルのハンドル
	int currentAnim_; // 現在再生中のアニメーションのID

	bool isPlay_; // アニメーションが再生中かどうか

	float time_; // アニメーションの再生時間
	float speed_; // アニメーションの再生速度
};