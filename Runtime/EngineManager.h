#pragma once
#include "DefaultLayer.h"

class EngineManager
{
public:
	static EngineManager* GetInstance();

	void SetDefaultLayer(shared_ptr<DefaultLayer> defaultLayer);
	DefaultLayer* GetDefaultLayer();

private:
	static std::unique_ptr<EngineManager> _instance;	
	static std::shared_ptr<DefaultLayer> _defaultLayer;
};

