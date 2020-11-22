#pragma once
#include <string>
#include <map>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class VisualComponent
{
public:
	VisualComponent();
	VisualComponent(const std::string& spriteFrameFilename, const std::string& animationFileName, const string& initialFrameName);
	Sprite* GetSprite() const noexcept;

	void RegisterAnimation(const string& animationName, float duration);
	void PlayAnimation(const string& animationName, float delta);

private:
	std::map<string, unique_ptr<Animate>> _animations;
	unique_ptr<Sprite> _sprite;
};

