#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model/Player.fbx");
	state = PLAYER_STATE_IDLE;
}

void Player::Update()
{
	switch(state){
		case PLAYER_STATE_IDLE:
			break;
		case PLAYER_STATE_WALK:
			if (Input::IsKey(DIK_W)) {

			}
			else if (Input::IsKey(DIK_S)) {

			}
			else if (Input::IsKey(DIK_A)) {

			}
			else if (Input::IsKey(DIK_D)) {

			}
			break;
		case PLAYER_STATE_JUMP:
			break;
		case PLAYER_STATE_ATTACK:
			break;
	}
}

void Player::Draw()
{
	Direct3D::SetShader(Direct3D::SHADER_3D);
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
