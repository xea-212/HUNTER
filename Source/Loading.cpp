#include "Loading.h"
#include "../Engine/Model.h"
#include "../Engine/SceneManager.h"

Loading::Loading()
	:GameObject(nullptr, "Loading"), isLoadEnd_(false)
{
}

Loading::~Loading()
{
}

void Loading::Initialize()
{
	Model::Load("Model/Character/Player.fbx");
	Model::Load("Model/Character/Enemy.fbx");
	Model::Load("Model/Stage/Ground.fbx");
	Model::Load("Model/Stage/Sky.fbx");

	Model::Load("Anim/Attack.fbx");
	Model::Load("Anim/Idle.fbx");
	Model::Load("Anim/Walk.fbx");
	Model::Load("Anim/Run.fbx");

	Model::Load("Anim/EDRun.fbx");
	Model::Load("Anim/EDunce.fbx");
	Model::Load("Anim/EFlex.fbx");
	Model::Load("Anim/EIdle.fbx");
	Model::Load("Anim/EJumpAttack.fbx");
	Model::Load("Anim/ERoar.fbx");
	Model::Load("Anim/EWalk.fbx");
	Model::Load("Anim/ERun.fbx");
	Model::Load("Anim/ESwip.fbx");

	isLoadEnd_ = true;
}

void Loading::Update()
{
	if (isLoadEnd_)
	{
		SceneManager* sceneManager = (SceneManager*)GetParent();
		sceneManager->ChangeScene(SCENE_ID::SCENE_ID_PLAY);
	}
}

void Loading::Draw()
{
	//ローディングのぐるぐる
}

void Loading::Release()
{
}
