#include "pch.h"
#include "EcgRuntime.h"

namespace EcgRuntime
{
	EcgRuntime::EcgRuntime()
		: _runtimeNative(new ::Runtime)
	{

	}

	EcgRuntime::~EcgRuntime()
	{		
		delete _runtimeNative;
		_runtimeNative = nullptr;
	}

	void EcgRuntime::Initialize(int parent)
	{
		_runtimeNative->initialize(parent);
		this->_isLoaded = true;	
	}

	void EcgRuntime::Destroy()
	{
		_runtimeNative->destroy();
		this->_isLoaded = false;
	}

	void EcgRuntime::CreateNewScene()
	{
		_runtimeNative->CreateScene();
	}
	
	void EcgRuntime::CreateNewScene(int speed)
	{
		_runtimeNative->CreateScene(speed);
	}

	void EcgRuntime::Run()
	{
		_runtimeNative->Run();
	}

	bool EcgRuntime::IsLoaded()
	{
		return this->_isLoaded;
	}


	void EcgRuntime::SwitchScene()
	{
		_runtimeNative->switchScene();
	}
}