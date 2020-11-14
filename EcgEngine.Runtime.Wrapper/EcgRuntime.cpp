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

	void EcgRuntime::Destroy()
	{
		_runtimeNative->destroy();
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

	void EcgRuntime::Initialize(int parent)
	{
		_runtimeNative->initialize(parent);
	}

	void EcgRuntime::SwitchScene()
	{
		_runtimeNative->switchScene();
	}
}