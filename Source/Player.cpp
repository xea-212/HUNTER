#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "StageObject.h"
#include "../Engine/CsvReader.h"
#include "Animator.h"
#include "../Engine/Time.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), isRun(false)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model/Character/Player.fbx");
	transform_.scale_ = { 0.05f, 0.05f, 0.05f };
	state = PLAYER_STATE_FREE;

	SetParameter("PlayerParam");

	animator = Instantiate<Animator>(this);
	animator->AttachAnimation("PlayerAnim");
	animator->Play(ANIM_IDLE); // 待機アニメーション
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
	Model::Draw(hModel_, animator->GetAnimHandle(), animator->GetTime());
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
	delete csv;

	maxHP = param_.hp_; // 最大体力を設定
}

void Player::Free()
{
	float speed = param_.speed_;

	// Shiftでダッシュ
	if (Input::IsKey(DIK_LSHIFT))
	{
		const float dashMultiplier = 2.0f; // ダッシュ時の速度倍率
		speed *= dashMultiplier;
		isRun = true;
	}

	float moveX = 0.0f;
	float moveZ = 0.0f;

	if(Input::IsKey(DIK_A)) {
		moveX -= speed;
	}
	if(Input::IsKey(DIK_W)) {
		moveZ += speed;
	}
	if (Input::IsKey(DIK_S)) {
		moveZ -= speed;
	}
	if(Input::IsKey(DIK_D)) {
		moveX += speed;
	}

	// マウス左クリックで攻撃
	if (Input::IsMouseButtonDown(0)) {
		state = PLAYER_STATE_ATTACK_MAIN;
	}

	// 入力時のみ
	if (moveX != 0.0f || moveZ != 0.0f) {

		float yaw = Camera::GetYaw();

		// カメラ基準移動
		float dirX = moveX * cosf(yaw) + moveZ * sinf(yaw);
		float dirZ = -moveX * sinf(yaw) + moveZ * cosf(yaw);

		// 正規化
		float length = sqrtf(dirX * dirX + dirZ * dirZ);

		if (length > 0.0f) {
			dirX /= length;
			dirZ /= length;
		}

		// 向きたい角度
		float targetRotY = XMConvertToDegrees(atan2f(dirX, dirZ));

		// 現在角度
		float currentRotY = transform_.rotate_.y;

		// 角度差
		float diff = targetRotY - currentRotY;

		while (diff > 180.0f) diff -= 360.0f;
		while (diff < -180.0f) diff += 360.0f;

		// 補間
		currentRotY += diff * 0.15f;

		transform_.rotate_.y = currentRotY;

		// 移動
		vPos += XMVectorSet(
			dirX * speed,
			0,
			dirZ * speed,
			0
		);

		if (isRun) {
			animator->Play(ANIM_RUN); // ダッシュアニメ
			isRun = false;
		}
		else {
			animator->Play(ANIM_WALK); // 移動アニメ
		}
	}
	else {
		animator->Play(ANIM_IDLE); // 待機
	}
}

void Player::Attack()
{
	state = PLAYER_STATE_FREE;
}
