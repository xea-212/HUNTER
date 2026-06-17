#include "Enemy.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"
#include "../Engine/Time.h"
#include "../Engine/CsvReader.h"
#include "Player.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), pPos{}, isAttack(false), dx_(0), dz_(0), distance_(0), timer_(0)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model/Character/Enemy.fbx");
	state = ENEMY_STATE_IDLE;

	animator = Instantiate<Animator>(this);
	animator->AttachAnimation("EnemyAnim");
	animator->Play(ENEMY_ANIM_IDLE); // 待機アニメーション
}

void Enemy::Update()
{
	Player* player = (Player*)GetParent()->FindChildObject("Player");
	pPos = player->GetTransform();

	UpdatePlayerInfo();

	switch (state) {
		case ENEMY_STATE_IDLE:
			Idle();
			break;
		case ENEMY_STATE_FIND:
			Find();
			break;
		case ENEMY_STATE_CHASE:
			Chase();
			break;
		case ENEMY_STATE_ATTACK:
			Attack();
			break;
		case ENEMYSTATE_COOLDOWN:
			Cooldown();
			break;
		case ENEMY_STATE_DAMAGE:
			Damage();
			break;
	}

}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, animator->GetAnimHandle(), animator->GetFrame());
}

void Enemy::Release()
{
}

void Enemy::SetParameter(std::string fileName)
{
	std::string path = "Data/";
	CsvReader* csv = new CsvReader(path + fileName + ".csv");

	constexpr int paramColumn = 1; // パラメーターの列番号
	for (int line = 0; line < csv->GetLines(); line++) {
		transform_.position_ = { csv->GetFloat(PLAYER_POSITION, COLUMN_POSITION_X), csv->GetFloat(PLAYER_POSITION, COLUMN_POSITION_Y), csv->GetFloat(PLAYER_POSITION, COLUMN_POSITION_Z) };
		transform_.rotate_ = { csv->GetFloat(PLAYER_ROTATE, COLUMN_ROTATE_X), csv->GetFloat(PLAYER_ROTATE, COLUMN_ROTATE_Y), csv->GetFloat(PLAYER_ROTATE, COLUMN_ROTATE_Z) };
		transform_.scale_ = { csv->GetFloat(PLAYER_SCALE, COLUMN_SCALE_X), csv->GetFloat(PLAYER_SCALE, COLUMN_SCALE_Y), csv->GetFloat(PLAYER_SCALE, COLUMN_SCALE_Z) };
		param_.hp_ = csv->GetInt(PLAYER_HP, paramColumn);
		param_.power_ = csv->GetInt(PLAYER_POWER, paramColumn);
		param_.speed_ = csv->GetFloat(PLAYER_SPEED, paramColumn);
		param_.velocity_ = { 0, csv->GetFloat(PLAYER_VELOCITY, paramColumn), 0 };
		param_.gravity_ = csv->GetFloat(PLAYER_GRAVITY, paramColumn);
	}
	delete csv;
}

void Enemy::UpdatePlayerInfo()
{
	dx_ = pPos.position_.x - transform_.position_.x;
	dz_ = pPos.position_.z - transform_.position_.z;
	distance_ = sqrtf(dx_ * dx_ + dz_ * dz_);
}

void Enemy::Idle()
{
}

void Enemy::Find()
{

}

void Enemy::Chase()
{
}

void Enemy::Attack()
{
}

void Enemy::Cooldown()
{
	timer_ += Time::DeltaTime();

	const float cooldownDuration = 2.0f; // クールダウン時間（秒）
	if (timer_ >= cooldownDuration) {
		timer_ = 0; // タイマーをリセット
		state = ENEMY_STATE_FIND; // 再びプレイヤーを探す状態に遷移
	}
}

void Enemy::Damage()
{	
}
