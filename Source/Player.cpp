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
	transform_.scale_ = { 0.05f, 0.05f, 0.05f };
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

	constexpr int paramColumn = 1; // パラメーターの列番号
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
	float moveX = 0.0f;
	float moveZ = 0.0f;

	if(Input::IsKey(DIK_A)) {
		moveX -= param_.speed_;
	}
	if(Input::IsKey(DIK_W)) {
		moveZ += param_.speed_;
	}
	if(Input::IsKey(DIK_S)) {
		moveZ -= param_.speed_;
	}
	if(Input::IsKey(DIK_D)) {
		moveX += param_.speed_;
	}

	// 入力時のみ
	if (moveX != 0.0f || moveZ != 0.0f) {
		float yaw = Camera::GetYaw();

		// カメラの向きに合わせて移動方向を計算
		float dirX = moveX * cosf(yaw) - moveZ * sinf(yaw);
		float dirZ = moveX * sinf(yaw) + moveZ * cosf(yaw);

		// ベクトルの長さを計算
		float length = sqrtf(dirX * dirX + dirZ * dirZ);

		if (length > 0.0f) {
			dirX /= length;
			dirZ /= length;
		}

		// 回転
		transform_.rotate_.y = XMConvertToDegrees(atan2f(dirX, dirZ));

		// 移動
		vPos += XMVectorSet(dirX * param_.speed_, 0, dirZ * param_.speed_, 0);
	}
}

void Player::Attack()
{
}
