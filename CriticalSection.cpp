#include "main.h"
#include "CriticalSection.h"
 
PerfLib::CriticalSection::CriticalSection()
{
	*((BYTE*)this + 24) = 0;
	*(DWORD*)this = 0;
	*((DWORD*)this + 1) = 0;
	*((DWORD*)this + 2) = 0;
	*((DWORD*)this + 3) = 0;
	*((DWORD*)this + 4) = 0;
	*((DWORD*)this + 5) = 0;
}

void* PerfLib::CriticalSection::operator=(const void* a2)
{
	void* result; // eax

	result = this;
	memcpy(this, a2, 0x1Cu);
	return result;
}

void PerfLib::CriticalSection::Lock(LPCRITICAL_SECTION lpCriticalSection)
{
	EnterCriticalSection(lpCriticalSection);
}

void PerfLib::CriticalSection::Unlock(LPCRITICAL_SECTION lpCriticalSection)
{
	LeaveCriticalSection(lpCriticalSection);
}

void PerfLib::CriticalSection::Dispose(LPCRITICAL_SECTION lpCriticalSection)
{
	if (!LOBYTE(lpCriticalSection[1].DebugInfo))
	{
		DeleteCriticalSection(lpCriticalSection);
	}
}

 unsigned int PerfLib::CriticalSection::Initialize(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount)
{
	if (dwSpinCount)
		InitializeCriticalSectionAndSpinCount(lpCriticalSection, dwSpinCount);
	else
		InitializeCriticalSection(lpCriticalSection);
	return 0;
}

