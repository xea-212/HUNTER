#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Model.h"
#include "../Engine/CsvReader.h"

class Stage : public GameObject
{
public:
	//コンストラクタ
	Stage(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
private:
	int hModel_;
	CsvReader* csv;
};