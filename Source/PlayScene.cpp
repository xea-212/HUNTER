#include "PlayScene.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"

PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
}

void PlayScene::Update()
{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* sceneManager = (SceneManager*)GetParent();
		sceneManager->ChangeScene(SCENE_ID::SCENE_ID_RESULT);
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
