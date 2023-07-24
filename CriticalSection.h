#pragma once
#include <Windows.h>

namespace PerfLib {

	class CriticalSection
	{
	public:
		CriticalSection();
		void* operator=(const void* a2);
		void Lock(LPCRITICAL_SECTION lpCriticalSection);
		void Unlock(LPCRITICAL_SECTION lpCriticalSection);
		void Dispose(LPCRITICAL_SECTION lpCriticalSection);
		unsigned int Initialize(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount);
	};
}


