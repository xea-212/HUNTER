#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "StageObject.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), moveWork(false), moveRotate(false), hp_(100), power_(10), vPos{},
	moveJump(false), isGround(false), moveAttack(false), gravity(0.0f), velocity(XMVectorZero())
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model/Character/Player.fbx");
	state = PLAYER_STATE_IDLE;
}

void Player::Update()
{
	vPos = XMLoadFloat3(&transform_.position_);

	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x)) *
		XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	moveWork = false;

	//	移動
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_S) || Input::IsKey(DIK_A) || Input::IsKey(DIK_D)){
		moveWork = true;
	}
	// 回転
	if(Input::IsKey(DIK_RIGHT) || Input::IsKey(DIK_LEFT)){
		moveRotate = true;
	}
	// ジャンプ
	if (Input::IsKeyDown(DIK_SPACE)) {
		moveJump = true;
		isGround = false;

	}

	//回転
	if (moveRotate) {
		if (Input::IsKey(DIK_RIGHT)) {
			transform_.rotate_.y += 1.0f;
		}
		else if (Input::IsKey(DIK_LEFT)) {
			transform_.rotate_.y -= 1.0f;
		}
		moveRotate = false;
	}

	// 状態の更新
	XMVECTOR mForward = {0,0,0,0};
	switch(state){
		case PLAYER_STATE_IDLE:
			Idle();
			break;
		case PLAYER_STATE_WALK:
			Walk();
			break;
		case PLAYER_STATE_JUMP:
			Jump();
			break;
		case PLAYER_STATE_ATTACK:
			Attack();
			break;
	}

	XMStoreFloat3(&transform_.position_, vPos);

	// レイキャスト
	StageObject* sObj = (StageObject*)GetParent()->FindChildObject("StageObject");
	int hGoundModel = sObj->getModelhundle();

	RayCastData data;
	data.start = {0, transform_.position_.y + 5.0f, 0};

	data.dir = { 0, -1, 0 };
	Model::RayCast(hGoundModel, &data);

	if(data.hit) {
		transform_.position_.y = data.start.y - data.dist;
	}

	// カメラの位置と向きの更新
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

void Player::Idle()
{
	
	if (moveWork) {
		state = PLAYER_STATE_WALK;
	}
	if (moveJump) {
		state = PLAYER_STATE_JUMP;
	}
}

void Player::Walk()
{
	if(!moveWork) {
		state = PLAYER_STATE_IDLE;
	}

	XMVECTOR move = XMVectorZero();

	if (Input::IsKey(DIK_W)) {
		move += XMVectorSet(0, 0, 0.1f, 0);
	}
	if (Input::IsKey(DIK_S)) {
		move += XMVectorSet(0, 0, -0.1f, 0);
	}
	if (Input::IsKey(DIK_A)) {
		move += XMVectorSet(-0.1f, 0, 0, 0);
	}
	if (Input::IsKey(DIK_D)) {
		move += XMVectorSet(0.1f, 0, 0, 0);
	}

	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	move = XMVector3TransformCoord(move, mRotate);

	vPos += move;
}

void Player::Jump()
{
	if (isGround && !moveJump) {
		state = PLAYER_STATE_IDLE;
	}

	XMVECTOR move = XMVectorZero();

	if (Input::IsKey(DIK_W)) {
		move += XMVectorSet(0, 0, 0.1f, 0);
	}
	if (Input::IsKey(DIK_S)) {
		move += XMVectorSet(0, 0, -0.1f, 0);
	}
	if (Input::IsKey(DIK_A)) {
		move += XMVectorSet(-0.1f, 0, 0, 0);
	}
	if (Input::IsKey(DIK_D)) {
		move += XMVectorSet(0.1f, 0, 0, 0);
	}

	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	move = XMVector3TransformCoord(move, mRotate);

	vPos += move;

	// ジャンプ
	vPos += XMVectorSet(0, velocity, 0, 0);
}

void Player::Attack()
{
}
