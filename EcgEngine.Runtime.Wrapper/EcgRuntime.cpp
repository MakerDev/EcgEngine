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
		_runtimeNative->Destroy();
	}

	void EcgRuntime::Initialize(int parent)
	{
		_runtimeNative->Initilaize(parent);
	}

	void EcgRuntime::SwitchScene()
	{
		_runtimeNative->SwitchScene();
	}
}