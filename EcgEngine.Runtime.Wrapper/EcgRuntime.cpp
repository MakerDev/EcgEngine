#include <string>
#include <iostream>

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

	void EcgRuntime::CreateNewScene(String^ filename)
	{
		std::string filenameConverted;
		marshalToString(filename, &filenameConverted);
		_runtimeNative->CreateScene(filenameConverted);
	}

	void EcgRuntime::Run()
	{
		_runtimeNative->Run();
	}

	bool EcgRuntime::IsLoaded()
	{
		return this->_isLoaded;
	}

	void EcgRuntime::marshalToString(String^ s, std::string* outString)
	{
		using namespace System::Runtime::InteropServices;

		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();

		*outString = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	void EcgRuntime::SwitchScene()
	{
		_runtimeNative->switchScene();
	}
}