#pragma once
#include <vector>

#include "cocos2d.h"
#include "RuntimeAction.h"

using namespace std;
using namespace cocos2d;

class GameObject : public Node
{
public:
	static shared_ptr<GameObject> createFromJson(string filename);
	Point position;
	Size size;

	//TODO: Encapsulate all sprite and animation related fields to seperate component ex) Visual
	Sprite* sprite;

	float getScaleFactor() const noexcept;
	void setScaleFactor(float scaleFactor);

	virtual void onUpdate(float delta, const vector<EventKeyboard::KeyCode>& heldKeys);

private:
	//TODO: 적절한 key를 선택하고 map으로 구조를 바꿔효율 높이기
	//TODO : change to smart pointers
	std::vector<shared_ptr<RuntimeAction>> _keyboardTriggeredActions;

	void addAction(string name, void* param);

	float _scaleFactor = 1.0F;
};

