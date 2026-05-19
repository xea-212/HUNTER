#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "StageObject.h"
#include "../Engine/CsvReader.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model/Character/Player.fbx");
	state = PLAYER_STATE_FREE;

	SetParameter("PlayerParam");
}

void Player::Update()
{
	vPos = XMLoadFloat3(&transform_.position_);

	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x)) *
		XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	XMVECTOR mForward = {0,0,0,0};
	switch(state){
		case PLAYER_STATE_FREE:
			Free();
			break;
		case PLAYER_STATE_ATTACK_MAIN:
			Attack();
			break;
		case PLAYER_STATE_ATTACK_SUB:
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

	// プレイヤーから見たカメラの位置と向きの更新
	constexpr int camHeight = 20; // カメラの高さ
	constexpr int camDistance = -20; // カメラとプレイヤーの距離（Z軸方向）
	XMVECTOR vCam = {0,camHeight,camDistance,0};
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

void Player::SetParameter(std::string fileName)
{
	std::string path = "Data/";
	CsvReader* csv = new CsvReader(path + fileName + ".csv");

	const int paramColumn = 1; // パラメーターの列番号
	for (int line = 0; line < csv->GetLines(); line++) {
		param_.hp_ = csv->GetInt(PLAYER_HP, paramColumn);
		param_.power_ = csv->GetInt(PLAYER_POWER, paramColumn);
		param_.speed_ = csv->GetFloat(PLAYER_SPEED, paramColumn);
		param_.velocity_ = { 0, csv->GetFloat(PLAYER_VELOCITY, paramColumn), 0 };
		param_.gravity_ = csv->GetFloat(PLAYER_GRAVITY, paramColumn);
	}
}

void Player::Free()
{
	if(Input::IsKey(DIK_A)) {
		vPos += {-param_.speed_, 0, 0, 0};
	}
	if(Input::IsKey(DIK_W)) {
		vPos += {0, 0, param_.speed_, 0};
	}
	if(Input::IsKey(DIK_S)) {
		vPos += {0, 0, -param_.speed_, 0};
	}
	if(Input::IsKey(DIK_D)) {
		vPos += {param_.speed_, 0, 0, 0};
	}

	if(Input::IsKey(DIK_SPACE)) {
		vPos += param_.velocity_;
	}

}

void Player::Attack()
{
}
