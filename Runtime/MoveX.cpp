#include <functional>

#include "MoveX.h"
#include "RuntimeActionTemplates.h"
#include "ActionArgument.h"

void MoveX::AddActionFromJson(GameObject* targetGameObject, 
						      RuntimeAction* runtimeAction, 
						      const rapidjson::Value& actionValueObject)
{
	const auto& arguments = actionValueObject["Arguments"].GetArray();

	//TODO : 여기도 템플릿을 각 클래스로 만들어서 매개변수 같은거 제대로 설정편하게 하돌고 바꾸자
	//각 템플릿 내부에서 Arguments를 받아서 처리하거나한다. 아래와 같은 바인딩할 함수도 좀 미리 만들어두고

	//Arg1 : Direction
	std::function<void(void)> flipFalse = 
		std::bind(RuntimeActionTemplates::FlipSpriteXFalse, targetGameObject);
	std::function<void(void)> flipTrue = 
		std::bind(RuntimeActionTemplates::FlipSpriteXTrue, targetGameObject);

	const ActionArgument arg1(arguments[0]);

	if (arg1.GetValue().compare("Right") == 0)
	{
		runtimeAction->PushFunctiona(flipTrue);
	}
	else
	{
		runtimeAction->PushFunctiona(flipFalse);
	}

	const ActionArgument arg2(arguments[1]);
	//Value값이 generic이라서 string이기 때문. 타입보고 변환해줄필요있음
	int velocity = stoi(arg2.GetValue());
	std::function<void(void)> moveFunc = std::bind(RuntimeActionTemplates::MoveX, targetGameObject, velocity);

	runtimeAction->PushFunctiona(moveFunc);
}
