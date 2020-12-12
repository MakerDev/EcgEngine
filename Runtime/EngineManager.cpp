#include "EngineManager.h"

//Static variable init
std::unique_ptr<EngineManager> EngineManager::_instance = nullptr;
std::shared_ptr<DefaultLayer> EngineManager::_defaultLayer = nullptr;

EngineManager* EngineManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = make_unique<EngineManager>();
	}

	return _instance.get();
}

EngineManager::EngineManager()
	:_packageName("")
{

}

void EngineManager::SetDefaultLayer(shared_ptr<DefaultLayer> defaultLayer)
{
	_defaultLayer = defaultLayer;
}

DefaultLayer* EngineManager::GetDefaultLayer()
{
	return _defaultLayer.get();
}

const string& EngineManager::GetPackageName() const
{
	return _packageName;
}

void EngineManager::SetPackageName(const string& packageName)
{
	_packageName = packageName;
}
