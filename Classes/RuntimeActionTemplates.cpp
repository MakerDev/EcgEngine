#include "RuntimeActionTemplates.h"

void RuntimeActionTemplates::MoveX(GameObject* target, float delta)
{
	target->position.x += delta;
	target->sprite->setPositionX(target->sprite->getPositionX() + delta);
}

void RuntimeActionTemplates::FlipSpriteXTrue(GameObject* target)
{
	target->sprite->setFlippedX(true);
}

void RuntimeActionTemplates::FlipSpriteXFalse(GameObject* target)
{
	target->sprite->setFlippedX(false);
}

void RuntimeActionTemplates::FlipSpriteX(GameObject* target)
{
	target->sprite->setFlippedX(target->sprite->isFlippedX());
}
