#include "Enemy.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"
#include "../Engine/Time.h"
#include "../Engine/CsvReader.h"
#include "Player.h"
#include "StageObject.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), pPos{}, isAttack(false), dx_(0), dz_(0), distance_(0), timer_(0), isFlex(false)
	, isAttackSelect(0), attackID_(0)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model/Character/Enemy.fbx");
	state = ENEMY_STATE_IDLE;

	SetParameter("EnemyParam");

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
		case ENEMY_STATE_COOLDOWN:
			Cooldown();
			break;
		case ENEMY_STATE_DAMAGE:
			Damage();
			break;
	}

	StageObject* sObj = (StageObject*)GetParent()->FindChildObject("StageObject");
	int hGoundModel = sObj->getModelhundle();

	RayCastData data;
	data.start = transform_.position_;
	const float topOffset = 100.0f;
	data.start.y = transform_.position_.y + topOffset; // プレイヤーの頭上からレイを発射

	data.dir = { 0, -1, 0 };
	Model::RayCast(hGoundModel, &data);

	if (data.hit) {
		transform_.position_.y = data.start.y - data.dist;
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

	dirX_ = dx_ / distance_;
	dirZ_ = dz_ / distance_;

	distance_ = sqrtf(dx_ * dx_ + dz_ * dz_);
}

bool Enemy::CanSeePlayer()
{
	if (distance_ > 40.0f) { // プレイヤーが40ユニット以内にいる場合
		return false;
	}
	if (distance_ <= 0.001f) {
		return true; // プレイヤーと敵がほぼ同じ位置にいる場合も見えるとする
	}

	float rad = XMConvertToRadians(transform_.rotate_.y);

	float forwardX = sinf(rad);
	float forwardZ = cosf(rad);

	float dot = forwardX * dirX_ + forwardZ * dirZ_;

	return dot > cosf(XMConvertToRadians(60.0f)); // 視野角60度以内にプレイヤーがいるかどうかを判定
}

void Enemy::Idle()
{
	animator->Play(ENEMY_ANIM_IDLE); // 待機アニメーション
	if (CanSeePlayer()) {
		isFlex = true; // プレイヤーを見つけたフラグを立てる
		state = ENEMY_STATE_FIND; // プレイヤーを見つけたら探索状態に遷移
	}
}

void Enemy::Find()
{
	if (isFlex) {
		animator->Play(ENEMY_ANIM_FLEX); // 歩行アニメーション
		isFlex = false;
	}
	if (!animator->IsPlaying()) {
		state = ENEMY_STATE_CHASE;
	}
}

void Enemy::Chase()
{
	animator->Play(ENEMY_ANIM_WALK);

	if (distance_ <= 10.0f) {
		state = ENEMY_STATE_ATTACK; // 攻撃状態に遷移
	}

	transform_.position_.x += dirX_ * param_.speed_;
	transform_.position_.z += dirZ_ * param_.speed_;

	transform_.rotate_.y = atan2f(dirX_, dirZ_) * (180.0f / XM_PI); // プレイヤーの方向を向く

	if (!CanSeePlayer()) {
		state = ENEMY_STATE_IDLE; // プレイヤーが見えなくなったら待機状態に遷移
	}
}

void Enemy::Attack()
{
	if(!isAttackSelect){
		attackID_ = rand() % 3; // 0, 1, 2のランダムな値を生成

		switch(attackID_){
			case 0:
				animator->Play(ENEMY_ANIM_JATTACK); // 攻撃アニメーション1
				break;
			case 1:
				animator->Play(ENEMY_ANIM_ROAR); // 攻撃アニメーション2
				break;
			case 2:
				animator->Play(ENEMY_ANIM_SWIP); // 攻撃アニメーション3
				break;
		}
		isAttackSelect = true;
	}

	if (!animator->IsPlaying()) {
		isAttack = false; // 攻撃終了
		state = ENEMY_STATE_COOLDOWN; // クールダウン状態に遷移
	}
}

void Enemy::Cooldown()
{
	timer_ += Time::DeltaTime();

	const float cooldownDuration = 2.0f; // クールダウン時間（秒）
	if (timer_ >= cooldownDuration) {
		timer_ = 0; // タイマーをリセット
		state = ENEMY_STATE_CHASE; // 再びプレイヤーを探す状態に遷移
	}
}

void Enemy::Damage()
{	
}
