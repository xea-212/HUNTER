#include "PlayScene.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "Sky.h"
#include "Player.h"
#include "Enemy.h"
#include "StageObject.h"
#include "StageManager.h"
#include "HpBar.h"

PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
	Camera::SetEnableControl(true);
	ShowCursor(false);

	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	Instantiate<Sky>(this);
	Instantiate<StageManager>(this);
	Instantiate<StageObject>(this);
	Instantiate<HpBar>(this);
}

void PlayScene::Update()
{
	Player* player = (Player*)FindChildObject("Player");
	if (player->GetHP() <= 0)
	{
		SceneManager* sceneManager = (SceneManager*)GetParent();
		sceneManager->ChangeScene(SCENE_ID::SCENE_ID_RESULT);
	}

	XMFLOAT3 target = player->GetPosition();
	const float topOffset = 5.0f; // プレイヤーの頭上に焦点を設定するためのオフセット
	target.y += topOffset; // プレイヤーの頭上に焦点を設定
	Camera::SetTarget(target);
	
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
