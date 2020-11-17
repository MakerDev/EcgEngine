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
		void CreateNewScene(int speed);
		void Run();
		bool IsLoaded();

	private:
		::Runtime* _runtimeNative;
		bool _isLoaded = false;
	};
}

