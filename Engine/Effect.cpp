#include "Effect.h"

Effect::Effect()
{
    timer_ = 0.0f;
    life_ = 0.0f;
    dead_ = false;
    size_ = 1.0f;
}

Effect::~Effect()
{
}

void Effect::Create(const char* filename, XMFLOAT3 pos, float lifetime, float size)
{
    texture_.Load(filename);

    position_ = pos;

    timer_ = 0.0f;
    life_ = lifetime;

    size_ = size;

    dead_ = false;
}

void Effect::Update()
{
    timer_ += 1.0f / 60.0f;

    if (timer_ >= life_) {
        dead_ = true;
    }
}

void Effect::Draw()
{
    if (dead_) {
        return;
    }
}

bool Effect::IsDead() const
{
    return false;
}
