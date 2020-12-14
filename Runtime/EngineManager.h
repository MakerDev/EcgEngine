#pragma once
#include "DefaultLayer.h"

class EngineManager
{
public:
	static EngineManager* GetInstance();

	EngineManager();

	static DefaultLayer* CreateDefaultLayer(const string& filename);
	void SetDefaultLayer(DefaultLayer* defaultLayer);
	DefaultLayer* GetDefaultLayer();
	const string& GetPackageName() const;
	void SetPackageName(const string& packageName);

private:
	std::string _packageName = "";
	static std::unique_ptr<EngineManager> _instance;
	//static std::shared_ptr<DefaultLayer> _defaultLayer;
	static DefaultLayer* _defaultLayer;
};

