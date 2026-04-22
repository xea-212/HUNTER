#include "TitleScene.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "TitleUI.h"

//コンストラクタ
TitleScene::TitleScene(GameObject * parent)
	: GameObject(parent, "TitleScene")
{
}

//初期化
void TitleScene::Initialize()
{
	Instantiate<TitleUI>(this);
}

//更新
void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* sceneManager = (SceneManager*)GetParent();
		sceneManager->ChangeScene(SCENE_ID::SCENE_ID_PLAY);
	}
}

//描画
void TitleScene::Draw()
{

}

//開放
void TitleScene::Release()
{
}
