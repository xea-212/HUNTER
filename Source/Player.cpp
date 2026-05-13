#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), moveWork(false), moveRotate(false), hp_(100), power_(10)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model/Player.fbx");
	state = PLAYER_STATE_IDLE;
}

void Player::Update()
{
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x)) *
		               XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	moveWork = false;

	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_S) || Input::IsKey(DIK_A) || Input::IsKey(DIK_D)){
		moveWork = true;
	}
	if(Input::IsKey(DIK_RIGHT) || Input::IsKey(DIK_LEFT)){
		moveRotate = true;
	}

	XMVECTOR mForward = {0,0,0,0};
	switch(state){
		case PLAYER_STATE_IDLE:
			if (moveRotate) {
				if (Input::IsKey(DIK_RIGHT)) {
					transform_.rotate_.y += 1.0f;
				}
				else if (Input::IsKey(DIK_LEFT)) {
					transform_.rotate_.y -= 1.0f;
				}
				moveRotate = false;
			}
			if (moveWork){
				state = PLAYER_STATE_WALK;
			}
			break;
		case PLAYER_STATE_WALK:
			if (!moveWork) {
				state = PLAYER_STATE_IDLE;
			}

			if (Input::IsKey(DIK_W)) {
				vPos += XMVectorSet(0, 0, 0.001f, 0);
			}
			if (Input::IsKey(DIK_S)) {
				vPos += XMVectorSet(0, 0, -0.001f, 0);
			}
			if (Input::IsKey(DIK_A)) {
				vPos += XMVectorSet(-0.001f, 0, 0, 0);
			}
			if (Input::IsKey(DIK_D)) {
				vPos += XMVectorSet(0.001f, 0, 0, 0);
			}
			
			break;
		case PLAYER_STATE_JUMP:
			break;
		case PLAYER_STATE_ATTACK:
			break;
	}

	XMVECTOR rotateMove = XMVector3TransformCoord(vPos, mRotate);
	vPos += rotateMove;
	XMStoreFloat3(&transform_.position_, vPos);

	XMVECTOR vCam = {0,5,-20,0};
	vCam = XMVector3TransformCoord(vCam, mRotate);
	
	XMFLOAT3 camPos;
	XMStoreFloat3(&camPos, vPos + vCam);
	Camera::SetPosition(camPos);

	XMVECTOR vForward = XMVector3TransformCoord(XMVectorSet(0, 0, 1, 0), mRotate);

	XMFLOAT3 camTarget;
	XMStoreFloat3(&camTarget, vPos + vForward);

	Camera::SetTarget(camTarget);
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
