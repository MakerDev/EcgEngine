#include "EngineManager.h"

//Static variable init
std::unique_ptr<EngineManager> EngineManager::_instance = nullptr;
DefaultLayer* EngineManager::_defaultLayer = nullptr;

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

DefaultLayer* EngineManager::CreateDefaultLayer(const string& filename)
{
	auto defaultLayer = DefaultLayer::CreateDefaultLayerFromJson(filename);

	return defaultLayer;
}

void EngineManager::SetDefaultLayer(DefaultLayer* defaultLayer)
{
	_defaultLayer = defaultLayer;
}

DefaultLayer* EngineManager::GetDefaultLayer()
{
	return _defaultLayer;
}

const string& EngineManager::GetPackageName() const
{
	return _packageName;
}

void EngineManager::SetPackageName(const string& packageName)
{
	_packageName = packageName;
}
