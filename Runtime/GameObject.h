#pragma once
#include <vector>
#include <rapidjson/document.h>

#include "cocos2d.h"
#include "RuntimeAction.h"
#include "VisualComponent.h"

using namespace std;
using namespace cocos2d;

class GameObject : public Node
{
public:
	static unique_ptr<GameObject> CreateFromJsonValue(const rapidjson::Value& value);
	float GetScaleFactor() const noexcept;
	void SetScaleFactor(float scaleFactor);
	Point GetPosition() const;
	virtual void OnUpdate(float delta, const vector<EventKeyboard::KeyCode>& heldKeys, const vector<EventKeyboard::KeyCode>& releasedKeys);
	VisualComponent* GetVisual();
	VisualComponent* GetVisualConst() const;
	Sprite* GetSprite() const;

public:
	Point position;
	Size size;

private:
	//TODO : this is temporal
	void addActionFromJsonValue(const rapidjson::Value& value);

private:
	//TODO: 적절한 key를 선택하고 map으로 구조를 바꿔효율 높이기
	//TODO : change to smart pointers
	unique_ptr<VisualComponent> _visualComponent;
	std::vector<shared_ptr<RuntimeAction>> _keyboardTriggeredActions;
	float _scaleFactor = 1.0F;
};

