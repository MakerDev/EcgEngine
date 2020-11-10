#pragma once
#include "Runtime.h"

using namespace System;

namespace EcgRuntime
{
	public ref class EcgRuntime
	{
	private:
		::Runtime* _runtimeNative;

	public:
		EcgRuntime();
		virtual ~EcgRuntime();

		void Initialize(int parent);
		void SwitchScene();
		void Destroy();
		void CreateNewScene();
		void CreateNewScene(int speed);
	};
}

