#pragma once
#include <rapidjson/document.h>
#include <vector>
#include <functional>

#include "cocos2d.h"
#include "RuntimeAction.h"
#include "VisualComponent.h"
#include "VariableEngine.h"

using namespace std;
using namespace cocos2d;

class GameObject : public Node
{
public:
	static unique_ptr<GameObject> CreateFromJsonValue(const rapidjson::Value& value);
	float GetScaleFactor() const noexcept;
	void SetScaleFactor(float scaleFactor);
	Point GetPosition() const;
	string GetObjectName() const noexcept;

	virtual void OnUpdate(float delta, const vector<EventKeyboard::KeyCode>& heldKeys, const vector<EventKeyboard::KeyCode>& releasedKeys);
	VisualComponent* GetVisual() const noexcept;
	VisualComponent* GetVisualConst() const noexcept;
	Sprite* GetSprite() const noexcept;
	VariableEngine* GetLocalVariableEngine() noexcept;

	void RegisterAllActions();

	GameObject();

public:
	Point position;
	Size size;

private:
	//TODO : this is temporal
	void registerAllActionInternal(const rapidjson::Value&);
	void addActionFromJsonValue(const rapidjson::Value& value);
	void addNewVariableFromJsonValue(const rapidjson::Value& variableValue);

private:
	unique_ptr<VariableEngine> _localVariableEngine;
	function<void(void)> _registerActions;

	//TODO: 적절한 key를 선택하고 map으로 구조를 바꿔효율 높이기
	//TODO : change to smart pointers
	unique_ptr<VisualComponent> _visualComponent;
	std::vector<shared_ptr<RuntimeAction>> _keyboardTriggeredActions;
	float _scaleFactor = 2.0F;
	string _name = "";

	//HACK : dont do this
	unique_ptr<RuntimeAction> _gravity;
};

