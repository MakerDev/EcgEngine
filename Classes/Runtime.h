#pragma once

class Runtime
{
public:
	void Initilaize(int parent);
	void SwitchScene();
	void Destroy();

private:
	int _currentScene = 0;
};

