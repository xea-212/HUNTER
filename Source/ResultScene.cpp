#include "ResultScene.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"

ResultScene::ResultScene(GameObject* parent)
{
}

void ResultScene::Initialize()
{
}

void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SceneManager* sceneManager = (SceneManager*)GetParent();
		sceneManager->ChangeScene(SCENE_ID::SCENE_ID_TITLE);
	}
}

void ResultScene::Draw()
{
}

void ResultScene::Release()
{
}
