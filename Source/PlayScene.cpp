#include "PlayScene.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "Sky.h"
#include "Player.h"
#include "StageObject.h"
#include "StageManager.h"

PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
	Instantiate<Player>(this);
	//Instantiate<Sky>(this);
	Instantiate<StageManager>(this);
	Instantiate<StageObject>(this);
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
