#include "HpBar.h"

HpBar::HpBar(GameObject* parent)
	:UI(parent), player_(nullptr), hp_(0), maxHp_(0), rate_(0.0f)
{
}

void HpBar::Initialize()
{
	player_ = (Player*)GetParent()->FindChildObject("Player");
	hp_ = player_->GetHP();
	maxHp_ = player_->GetMaxHP();
}

void HpBar::Update()
{
	hp_ = player_->GetHP();
	rate_ = static_cast<float>(hp_) / static_cast<float>(maxHp_);
}

void HpBar::Draw()
{
}

void HpBar::Release()
{
}
