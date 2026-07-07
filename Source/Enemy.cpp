#include "Enemy.h"
#include "../Engine/Model.h"
#include "../Engine/Direct3D.h"
#include "../Engine/Time.h"
#include "../Engine/CsvReader.h"
#include "Player.h"
#include "StageObject.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), pPos{}, isAttack(false), dx_(0), dz_(0), distance_(0), 
	attacktimer_(0), chasetimer_(0), cooltimer_(0), isFlex_(false), maxHP_(0)
	, isAttackSelect(0), attackID_(0), flextimer_(0), dirX_(0), dirZ_(0), isShot(false)
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
		case ENEMY_STATE_SEARCH:
			Search();
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
	maxHP_ = param_.hp_;
	delete csv;
}

void Enemy::UpdatePlayerInfo()
{
	dx_ = pPos.position_.x - transform_.position_.x;
	dz_ = pPos.position_.z - transform_.position_.z;

	distance_ = sqrtf(dx_ * dx_ + dz_ * dz_);

	if (distance_ > 0.001f) {
		dirX_ = dx_ / distance_;
		dirZ_ = dz_ / distance_;
	}
}

bool Enemy::CanSeePlayer()
{
	if (distance_ > 100.0f) {
		return false;
	}
	if (distance_ <= 0.001f) {
		return true; // プレイヤーと敵がほぼ同じ位置にいる場合も見えるとする
	}

	float rad = XMConvertToRadians(transform_.rotate_.y);

	float forwardX = sinf(rad);
	float forwardZ = cosf(rad);

	float dot = forwardX * dirX_ + forwardZ * dirZ_;

	return dot > cosf(XMConvertToRadians(45.0f)); // 視野角60度以内にプレイヤーがいるかどうかを判定
}

void Enemy::Idle()
{
	animator->Play(ENEMY_ANIM_IDLE); // 待機アニメーション
	if (CanSeePlayer()) {
		isFlex_ = true; // プレイヤーを見つけたフラグを立てる
		state = ENEMY_STATE_FIND; // プレイヤーを見つけたら探索状態に遷移
	}
}

void Enemy::Find()
{
	if (isFlex_) {
		animator->Play(ENEMY_ANIM_FLEX);
		isFlex_ = false;
	}
	if (!animator->IsPlaying()) {
		state = ENEMY_STATE_CHASE;
	}
}

void Enemy::Chase()
{
	chasetimer_ += Time::DeltaTime();
	float speed = param_.speed_;

	const float low = maxHP_ * 0.3; // HPが3割以下になるとlowになった時の変数

	if (chasetimer_ <= 5.0f)
	{
		animator->Play(ENEMY_ANIM_WALK);
	}
	else
	{
		if (param_.hp_ <= low) {
			const float lowSpeed = 1.5f;
			speed *= lowSpeed;
			animator->Play(ENEMY_ANIM_DRUN);
		}
		else {
			const float defoRun = 2.0f;
			speed *= defoRun;
			animator->Play(ENEMY_ANIM_RUN);
		}
	}

	if (distance_ <= 10.0f) {
		chasetimer_ = 0.0f;
		state = ENEMY_STATE_ATTACK; // 攻撃状態に遷移
		return;
	}
	else if (!CanSeePlayer()) {
		chasetimer_ = 0.0f;

		searchTimer_ = 0.0f;
		SetSearchPos(); // 探索位置を設定

		state = ENEMY_STATE_SEARCH; // プレイヤーを見失ったら探索状態に遷移
		return;
	}

	transform_.position_.x += dirX_ * speed;
	transform_.position_.z += dirZ_ * speed;

	transform_.rotate_.y = atan2f(dirX_, dirZ_) * (180.0f / XM_PI); // プレイヤーの方向を向く
}

void Enemy::Attack()
{
	if (distance_ <= 15)
		animator->Play(ENEMY_ANIM_ROAR); // 攻撃アニメーション2
	else if (distance_ <= 30)
		animator->Play(ENEMY_ANIM_JATTACK); // 攻撃アニメーション1
	else if (distance_ <= 100) {
		animator->Play(ENEMY_ANIM_SWIP); // 攻撃アニメーション3
		if (!isShot && animator->GetFrame() >= 16) { // フレームが16以上になったら弾を撃つ
			eBullet = Instantiate<EnemyBullet>(GetParent());
			eBullet->Shot(transform_.position_, pPos.position_);
			isShot = true; // 弾を撃ったフラグを立てる
		}
	}

	if (!animator->IsPlaying()) {
		isAttackSelect = false; // 攻撃終了
		isShot = false; // 弾を撃ったフラグをリセット
		state = ENEMY_STATE_COOLDOWN; // クールダウン状態に遷移
	}
}

void Enemy::Cooldown()
{
	cooltimer_ += Time::DeltaTime();
	animator->Play(ENEMY_ANIM_IDLE);
	const float cooldownDuration = 2.0f; // クールダウン時間（秒）
	if (cooltimer_ >= cooldownDuration) {
		animator->Stop();
		cooltimer_ = 0; // タイマーをリセット
		state = ENEMY_STATE_CHASE; // 再びプレイヤーを探す状態に遷移
	}
}

void Enemy::Damage()
{	

}

void Enemy::SetSearchPos()
{
	constexpr float searchDistance = 30.0f;

	// 0～359度
	float angle = XMConvertToRadians((float)(rand() % 360));

	searchPos_.x = transform_.position_.x + sinf(angle) * searchDistance;
	searchPos_.y = transform_.position_.y;
	searchPos_.z = transform_.position_.z + cosf(angle) * searchDistance;
}

void Enemy::Search()
{
	animator->Play(ENEMY_ANIM_WALK);

	searchTimer_ += Time::DeltaTime();

	// 探索地点までのベクトル
	float dx = searchPos_.x - transform_.position_.x;
	float dz = searchPos_.z - transform_.position_.z;

	// 距離
	float dist = sqrtf(dx * dx + dz * dz);

	// 目的地に着いた、または5秒経過したら新しい目的地を決める
	if (dist < 1.0f || searchTimer_ > 5.0f)
	{
		searchTimer_ = 0.0f;
		SetSearchPos();
		return;
	}

	// 正規化
	dx /= dist;
	dz /= dist;

	// 移動
	transform_.position_.x += dx * param_.speed_;
	transform_.position_.z += dz * param_.speed_;

	// 向きを変更
	float targetRotate = atan2f(dx, dz) * (180.0f / XM_PI);

	// -180～180度に補正
	float diff = targetRotate - transform_.rotate_.y;

	while (diff > 180.0f) diff -= 360.0f;
	while (diff < -180.0f) diff += 360.0f;

	const float rotateSpeed = 3.0f;   // 1フレームで回る角度

	if (diff > rotateSpeed)
	{
		transform_.rotate_.y += rotateSpeed;
	}
	else if (diff < -rotateSpeed)
	{
		transform_.rotate_.y -= rotateSpeed;
	}
	else
	{
		transform_.rotate_.y = targetRotate;
	}

	// プレイヤーを見つけたら追跡
	if (CanSeePlayer())
	{
		searchTimer_ = 0.0f;
		state = ENEMY_STATE_CHASE;
		return;
	}

	// 一定時間探したら待機
	if (searchTimer_ >= 10.0f)
	{
		searchTimer_ = 0.0f;
		state = ENEMY_STATE_IDLE;
	}
}