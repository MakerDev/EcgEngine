#pragma once
#include "Runtime.h"

using namespace System;

namespace EcgRuntime
{
	public ref class EcgRuntime
	{
	public:
		EcgRuntime();
		virtual ~EcgRuntime();

		void Initialize(int parent);
		void SwitchScene();
		void Destroy();
		void CreateNewScene();
		void CreateNewScene(String^ filename);
		void Run();
		bool IsLoaded();

	private:
		void marshalToString(String^ s, std::string* outString);

	private:
		::Runtime* _runtimeNative;
		bool _isLoaded = false;
	};
}

