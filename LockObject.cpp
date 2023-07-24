#include "LockObject.h"
#include <Windows.h>
#include "CriticalSection.h"

void PerfLib::LockObject<PerfLib::CriticalSection>::Lock()
{
	EnterCriticalSection(*(LPCRITICAL_SECTION*)this);
	*(BYTE*)(this + 4) = 1;
}
 
void PerfLib::LockObject<PerfLib::CriticalSection>::Unlock()
{
	LeaveCriticalSection(*(LPCRITICAL_SECTION*)this);
	*(BYTE*)(this + 4) = 0;
}

PerfLib::LockObject<PerfLib::CriticalSection>::LockObject(LPCRITICAL_SECTION lpCriticalSection, char a3)
{
    *(DWORD*)this = lpCriticalSection;
    this[4] = 0;
    if (a3)
    {
        EnterCriticalSection(lpCriticalSection);
        this[4] = 1;
    }
    return this;
}