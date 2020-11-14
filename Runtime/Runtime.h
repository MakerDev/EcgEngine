#pragma once

//HACK : Never include cocos2d-related headers here. It will crash EcgEngine.Runtime.Wrapper's build.
#include <string>

class Runtime
{
public:
	void initialize(int parent);
	void switchScene();
	void destroy();
	void CreateScene();
	void CreateScene(int speed);
	void Run();
private:
	int _currentScene = 0;
};
