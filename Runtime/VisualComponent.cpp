#include "VisualComponent.h"

VisualComponent::VisualComponent()
{
	//Creates empty sprite for cases where the sprite is only needed for collision detection
	_sprite = unique_ptr<Sprite>(Sprite::create());
}

VisualComponent::VisualComponent(
	const std::string& spriteFrameFilename,
	const std::string& animationFileName,
	const string& initialFrameName)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(spriteFrameFilename);
	AnimationCache::getInstance()->addAnimationsWithFile(animationFileName);

	_sprite = unique_ptr<Sprite>(Sprite::createWithSpriteFrameName(initialFrameName));
}

Sprite* VisualComponent::GetSprite() const noexcept
{
	return _sprite.get();
}

void VisualComponent::RegisterAnimation(const string& animationName, float duration)
{
	AnimationCache* cache = AnimationCache::getInstance();
	Animation* animation = cache->getAnimation(animationName);

	assert(animation != nullptr && ("Couldn't find animation : " + animationName).c_str());

	Animate* animate = Animate::create(animation);

	animate->getAnimation()->setRestoreOriginalFrame(true);
	animate->setDuration(duration);
	animate->setTarget(_sprite.get());
	animate->retain();

	_animations.insert(pair<string, unique_ptr<Animate>>(animationName.c_str(), unique_ptr<Animate>(animate)));
}

void VisualComponent::PlayAnimation(const string& animationName, float delta)
{
	if (_animations.count(animationName) <= 0)
	{
		string msg = "Coundnt find animation with name" + animationName;
		assert(msg.c_str());

		return;
	}
	auto& animation = _animations[animationName];

	if (animation->isDone())
	{
		animation->startWithTarget(_sprite.get());
	}

	animation->step(delta);

	CCLOG("walking...");
}
