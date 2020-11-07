#pragma once
#include <vector>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class GameObject : public Node
{
public:
	Point position;
	Size size;

	//TODO: Encapsulate all sprite and animation related fields to seperate component ex) Visual
	Sprite* sprite;

	//TODO : Take held key infos
	virtual void onUpdate();
	virtual void onUpdate(vector<EventKeyboard::KeyCode>& heldKeys);

private:

};

