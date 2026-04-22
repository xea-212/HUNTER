#include "PlayScene.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "Sky.h"
#include "Stage.h"

PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
	Instantiate<Sky>(this);
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
