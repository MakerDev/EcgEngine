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
	void CreateScene(const std::string& filename);
	void CreateScene(const std::string& packagename, const std::string& jsonFileName);
	void Run();
private:
	int _currentScene = 0;
	bool _isAnimationStopped = false;
};
