#include "main.h"
#include "ServiceServer.h"

LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter;


LONG __stdcall TopLevelExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
    HANDLE FileA; // eax
    void* v2; // esi
    HANDLE CurrentProcess; // eax
    DWORD CurrentProcessId; // [esp-1Ch] [ebp-82Ch]
    int v6[3]; // [esp+0h] [ebp-810h] BYREF
    CHAR Filename[1024]; // [esp+Ch] [ebp-804h] BYREF
    CHAR FileName[1024]; // [esp+40Ch] [ebp-404h] BYREF

    WSAGetLastError();
    if (GetModuleFileNameA(0, Filename, 0x400u))
    {
        sprintf(FileName, "%s.dmp", Filename);
        FileA = CreateFileA(FileName, 0x40000000u, 0, 0, 2u, 0x80u, 0);
        v2 = FileA;
        if (FileA)
        {
            if (FileA != (HANDLE)-1)
            {
                v6[0] = GetCurrentThreadId();
                v6[1] = (int)ExceptionInfo;
                v6[2] = 0;
                CurrentProcessId = GetCurrentProcessId();
                CurrentProcess = GetCurrentProcess();
                MiniDumpWriteDump(
                    CurrentProcess,
                    CurrentProcessId,
                    v2,
                    MiniDumpNormal,
                    ExceptionInfo != 0 ? (PMINIDUMP_EXCEPTION_INFORMATION)v6 : 0,
                    0,
                    0);
                CloseHandle(v2);
            }
        }
    }
    return 0;
}


void __stdcall HandlerProc(DWORD dwControl)
{

    if (dwControl != SERVICE_CONTROL_STOP)
    {
        if (dwControl == SERVICE_CONTROL_INTERROGATE)
        {
            SetServiceStatus(hServiceStatus, &ServiceStatus);
            return;
        }
        if (dwControl != SERVICE_CONTROL_SHUTDOWN)
            return;
    }
    // sub_42EB00();
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;
    ServiceStatus.dwControlsAccepted = 1;
    ServiceStatus.dwCurrentState = 1;
    SetServiceStatus(hServiceStatus, &ServiceStatus);
}


DWORD* sub_42A810(DWORD* a) {
    int i;

    // Llamada a funciones desconocidas
    unknown_libname_1(a + 2142);
    PerfLib::AsyncWebRequest::AsyncWebRequest((PerfLib::AsyncWebRequest*)(a + 5961));
    sub_42A6E0(a + 6039);

    // Reiniciar valores del arreglo this
    *a = 0;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    a[4] = 0;
    a[5] = 0;
    a[6] = 0;
    a[7] = 0;
    a[8] = 0;

    // Reiniciar valores desde el índice 9 hasta 38 (inclusive) con 0
    memset(a + 9, 0, 0x28u);

    // Establecer valores específicos del arreglo this
    *((WORD*)a + 38) = 0;
    a[5751] = 0;
    a[5752] = 0;
    a[5753] = 0;
    a[5754] = 0;
    *((BYTE*)a + 78) = 0;
    a[20] = 0;
    *((BYTE*)a + 84) = 0;
    *((BYTE*)a + 85) = 0;
    a[22] = 0;
    a[23] = 0;
    *((BYTE*)a + 96) = 0;
    a[25] = 0;
    a[26] = 0;
    *((WORD*)a + 54) = 0;

    // Reiniciar valores desde el índice 110 hasta 173 (inclusive) con 0
    memset((char*)a + 110, 0, 0x64u);

    // Establecer valores específicos del arreglo this
    *((WORD*)a + 105) = 0;
    a[53] = 0;
    *((BYTE*)a + 216) = 0;
    a[55] = 0;
    *((WORD*)a + 112) = 0;
    a[57] = 0;
    a[58] = 0;
    a[59] = 0;
    *((WORD*)a + 120) = 0;
    a[61] = 0;
    a[62] = 0;
    a[63] = 0;
    a[64] = 0;
    a[65] = 0;
    *((WORD*)a + 132) = 0;
    a[67] = 0;
    a[69] = 0;
    a[70] = 0;
    a[71] = 0;
    a[72] = 0;
    a[73] = 0;
    a[74] = 0;
    a[75] = 0;
    a[76] = 0;
    a[77] = 0;
    a[78] = 0;
    a[79] = 0;
    a[80] = 0;
    a[81] = 0;
    a[82] = 0;
    *((BYTE*)a + 332) = 0;

    // Establecer valores específicos del arreglo a
    *(DWORD*)((char*)a + 333) = 0;
    *(DWORD*)((char*)a + 337) = 0;
    *(DWORD*)((char*)a + 341) = 0;
    *(DWORD*)((char*)a + 345) = 0;
    *(DWORD*)((char*)a + 349) = 0;
    *(DWORD*)((char*)a + 353) = 0;
    *(DWORD*)((char*)a + 357) = 0;
    *(DWORD*)((char*)a + 361) = 0;
    *((BYTE*)a + 365) = 0;

    // Reiniciar valores desde el índice 2463 hasta 2863 (inclusive) con 0
    memset(a + 2463, 0, 0x400u);

    // Reiniciar valores desde el índice 2719 hasta 3119 (inclusive) con 0
    memset(a + 2719, 0, 0x400u);

    // Establecer valores específicos del arreglo a
    a[92] = 0;
    *((WORD*)a + 186) = 0;
    a[5025] = 0;
    a[5024] = 0;
    a[5026] = 0;
    a[5027] = 0;
    a[5028] = 0;
    a[5029] = 0;
    *((BYTE*)a + 20092) = 0;
    a[5229] = 0;

    // Establecer valores específicos del arreglo a
    a[5230] = GetTickCount();
    a[5231] = 0;
    a[5232] = 0;
    a[5746] = 0;
    a[5750] = 0;
    a[5755] = 0;

    // Asignar memoria dinámica al arreglo a[5756]
    a[5756] = reinterpret_cast<DWORD>(operator new(0x80u));

    // Reiniciar valores desde el índice 0 hasta 127 (inclusive) del arreglo a[5756] con 0
    for (i = 0; i < 128; i += 4)
        *(DWORD*)(i + a[5756]) = 0;

    a[5233] = 0;

    // Llamada a función sub_41E470(a)
    sub_41E470(a);

    return a;
}



void* sub_42AAD0()
{
    void* result; // eax
    void* v1; // [esp+0h] [ebp-10h]

    result = Block;
    if (!Block)
    {
        v1 = operator new(0x5F44u);
        if (v1)
        {
            result = (void*)sub_42A810(v1);
            Block = result;
        }
        else
        {
            result = 0;
            Block = 0;
        }
    }
    return result;
}


bool sub_42EAE0()
{
    void* v1; // eax

    v1 = sub_42AAD0();
    return sub_42CEE0(v1) != 0;
}



LPTOP_LEVEL_EXCEPTION_FILTER ServiceProc(int a1, int a2)
{
    PerfLib::IPv4Address* v3; // ecx

    lpTopLevelExceptionFilter = SetUnhandledExceptionFilter(TopLevelExceptionFilter);
    ServiceStatus.dwServiceType = 16;
    ServiceStatus.dwCurrentState = 2;
    ServiceStatus.dwControlsAccepted = 1;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;
    hServiceStatus = RegisterServiceCtrlHandlerA(Buffer, HandlerProc);
    ServiceStatus.dwCurrentState = 4;
    SetServiceStatus(hServiceStatus, &ServiceStatus);
    if ((unsigned __int8)sub_42EAE0())
    {
        while (1)
        {
            v3->~IPv4Address();
            Sleep(0x3E8u);
        }
    }
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwCurrentState = 1;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;
    ServiceStatus.dwControlsAccepted = 1;
    SetServiceStatus(hServiceStatus, &ServiceStatus);
    return SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
}
