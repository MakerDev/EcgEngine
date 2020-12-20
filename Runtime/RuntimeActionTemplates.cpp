#include "RuntimeActionTemplates.h"

void RuntimeActionTemplates::MoveX(GameObject* target, float delta)
{
	target->position.x += delta;
	target->GetSprite()->setPositionX(target->GetSprite()->getPositionX() + delta);
}

void RuntimeActionTemplates::MoveY(GameObject* target, float delta)
{
	target->position.y -= delta;
	target->GetSprite()->setPositionY(target->GetSprite()->getPositionY() + delta);
}

void RuntimeActionTemplates::FlipSpriteXTrue(GameObject* target)
{
	target->GetSprite()->setFlippedX(true);
}

void RuntimeActionTemplates::FlipSpriteXFalse(GameObject* target)
{
	target->GetSprite()->setFlippedX(false);
}

void RuntimeActionTemplates::FlipSpriteX(GameObject* target)
{
	target->GetSprite()->setFlippedX(target->GetSprite()->isFlippedX());
}

void RuntimeActionTemplates::JumpBy(GameObject* target, float duration, int height)
{
	auto action = JumpBy::create(duration, Vec2(0,0), height, 1);
	target->GetSprite()->runAction(action);
}
