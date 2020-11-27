#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Player : public Node
{
public:
	enum State {
		Standing, Walking, Jumping
	};

	State state;

	bool facingRight;
	bool grounded;
	float stateTime;

	Size player_size;

	Point position;
	Point velocity;

	Player(void);
	virtual ~Player();
};

