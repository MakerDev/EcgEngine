#pragma once
#include "cocos2d.h"
using namespace cocos2d;

// KEYBOARD
const EventKeyboard::KeyCode ENTER = EventKeyboard::KeyCode::KEY_KP_ENTER;
const EventKeyboard::KeyCode UP_ARROW = EventKeyboard::KeyCode::KEY_UP_ARROW;
const EventKeyboard::KeyCode DOWN_ARROW = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
const EventKeyboard::KeyCode LEFT_ARROW = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
const EventKeyboard::KeyCode RIGHT_ARROW = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;


#ifndef _WIN32
    const float SCALE_FACTOR = 2.0f;
#else
    const float SCALE_FACTOR = 2.0f;
#endif

const float PLAYER_MAX_VELOCITY = 5.0f;
const float PLAYER_JUMP_VELOCITY = 10.0f;
const float DAMPING = 0.87f;
const float GRAVITY = 0.37f;
