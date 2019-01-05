#include "Effect.h"

Effect::Effect()
{
	FinishEffect = 0;
}

Effect::~Effect()
{
	delete EffectSprite;
	delete Size;
}

void Effect::Update(GameCamera * camera, int t)
{
	EffectSprite->Update(t);
}

void Effect::Draw(GameCamera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	EffectSprite->DrawFlipX(pos.x, pos.y);
}

int Effect::GetFinish()
{
	return FinishEffect;
}
