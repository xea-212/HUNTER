#include "PlayScene.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "Sky.h"
#include "Stage.h"
#include "Player.h"

PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
	Instantiate<Sky>(this);
	Instantiate<Stage>(this);
}

void PlayScene::Update()
{
	Player* player = (Player*)FindChildObject("Player");
	if (player->GetHP() <= 0)
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
