#include "IPv4Address.h"
#include <iostream>   
#include <Windows.h> 
#include <Dbghelp.h>

DWORD dword_456D84;
char* dword_454928; //checar

struct _SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hServiceStatus;

bool ConvertString(char** output, const char* a2) {
    CHAR Filename[1024];
    DWORD ModuleFileNameA = GetModuleFileNameA(0, Filename, 0x400u);
    if (!ModuleFileNameA)
        return false;

    int v5 = ModuleFileNameA - 1;
    if (v5 < 0)
        return false;

    while (Filename[v5] != 92) { // 92 es el valor ASCII para el carácter '\'
        if ((v5-- & 0x80000000) != 0)
            return false;
    }

    if (v5 == -1)
        return false;

    // Reserva memoria para el resultado y copia la parte de la ruta del archivo
    *output = new char[strlen(a2) + v5 + 2];
    memcpy(*output, Filename, v5 + 1);

    // Copia el nombre de archivo (a2) después de la ruta
    strcpy(*output + v5 + 1, a2);

    return true;
} 
 
bool sub_42EA70()
{
    PerfLib::IPv4Address* v0; // eax
    const struct sockaddr_in* SockAddr; // eax

    v0 = (PerfLib::IPv4Address*)operator new(4u);
    if (v0)
        SockAddr = v0->GetSockAddr();
    else
        SockAddr = 0;
    dword_456D84 = (int)SockAddr;
    
    if (ConvertString(&dword_454928, "worldserver.ini")) return true;
   
    return false;
}

bool CheckStringConfig(LPCSTR lpAppName, LPCSTR lpKeyName, LPSTR lpReturnedString, DWORD nSize)
{
    GetPrivateProfileStringA(lpAppName, lpKeyName, 0, lpReturnedString, nSize, dword_454928);
    return lpReturnedString && *lpReturnedString != 0;
}

bool CheckIntConfig(LPCSTR lpAppName, LPCSTR lpKeyName, int a4)
{
    UINT PrivateProfileIntA; // eax

    PrivateProfileIntA = GetPrivateProfileIntA(lpAppName, lpKeyName, -1, dword_454928);
    *(DWORD*)a4 = PrivateProfileIntA;
    return PrivateProfileIntA != -1;
}

void Console_Log(const char* Format, ...)
{
    CHAR OutputString[4096]; // [esp+0h] [ebp-1004h] BYREF
    
    va_list va; // [esp+100Ch] [ebp+8h] BYREF

    va_start(va, Format);
    vsprintf(OutputString, Format, va);
    OutputDebugStringA(OutputString);
}

int InstallServer()
{
    SC_HANDLE v0; // esi
    SC_HANDLE ServiceA; // eax
    CHAR Filename[512]; // [esp+4h] [ebp-204h] BYREF
 
     v0 = OpenSCManagerA(0, 0, 0xF003Fu);
    if (!v0)
        return 1;
    GetModuleFileNameA(0, Filename, 0x200u);
    if (ServiceStartName[0])
        ServiceA = CreateServiceA(v0, Buffer, DisplayName, 0xF01FFu,
            0x10u,
            3u,
            1u,
            Filename,
            0,
            0,
            0,
            ServiceStartName,
            &ReturnedString);
    else
        ServiceA = CreateServiceA(v0, Buffer, DisplayName, 0xF01FFu, 0x10u, 3u, 1u, Filename, 0, 0, 0, 0, 0);
    if (!ServiceA)
        return 2;
    CloseServiceHandle(ServiceA);
    CloseServiceHandle(v0);
    return 0;
}

int RemoveServer()
{
    SC_HANDLE v0; // eaxs
    SC_HANDLE v1; // edid
    SC_HANDLE v3; // esi
    struct _SERVICE_STATUS ServiceStatus; // [esp+4h] [ebp-1Ch] BYREF

    v0 = OpenSCManagerA(0, 0, 0xF003Fu);
    v1 = v0;
    if (!v0)
        return 1;
    v3 = OpenServiceA(v0, Buffer, 0xF01FFu);
    if (!v3)
        return 2;
    ControlService(v3, 1u, &ServiceStatus);
    if (!DeleteService(v3))
        return 4;
    CloseServiceHandle(v3);
    CloseServiceHandle(v1);
    return 0;
}

int StartServer()
{
    SC_HANDLE v0; // eax
    SC_HANDLE v1; // edi
    SC_HANDLE v3; // eax
    SC_HANDLE v4; // esi

    v0 = OpenSCManagerA(0, 0, 0xF003Fu);
    v1 = v0;
    if (!v0)
        return 1;
    v3 = OpenServiceA(v0, Buffer, 0xF01FFu);
    v4 = v3;
    if (!v3)
        return 2;
    if (StartServiceA(v3, 0, 0))
    {
        CloseServiceHandle(v4);
        CloseServiceHandle(v1);
        return 0;
    }
    else
    {
        GetLastError();
        return 3;
    }
}

int StopServer()
{
    SC_HANDLE v0; // eax
    SC_HANDLE v1; // edi
    SC_HANDLE v3; // esi
    struct _SERVICE_STATUS ServiceStatus; // [esp+4h] [ebp-1Ch] BYREF

    v0 = OpenSCManagerA(0, 0, 0xF003Fu);
    v1 = v0;
    if (!v0)
        return 1;
    v3 = OpenServiceA(v0, Buffer, 0xF01FFu);
    if (!v3)
        return 2;
    if (!ControlService(v3, 1u, &ServiceStatus))
        return 3;
    CloseServiceHandle(v3);
    CloseServiceHandle(v1);
    return 0;
}

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

LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter;

 

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

void* Block;

struct _RTL_CRITICAL_SECTION* __thiscall sub_42A6E0(struct _RTL_CRITICAL_SECTION* this)
{
    LOBYTE(this->DebugInfo) = 0;
    PerfLib::TcpSocket::TcpSocket((PerfLib::TcpSocket*)&this->LockCount);
    PerfLib::UdpSocket::UdpSocket((PerfLib::UdpSocket*)&this->SpinCount);
    PerfLib::ThreadPool::ThreadPool((PerfLib::ThreadPool*)&this[1].LockCount);
    this[5].RecursionCount = 0;
    this[5].OwningThread = 0;
    this[5].LockSemaphore = 0;
    this[5].SpinCount = 0;
    PerfLib::CriticalSection::CriticalSection((PerfLib::CriticalSection*)&this[6]);
    LOBYTE(this[7].LockCount) = 0;
    PerfLib::CriticalSection::Initialize(this + 6, 0);
    this[7].OwningThread = 0;
    this[7].LockSemaphore = 0;
    this[7].SpinCount = 0;
    this[8].DebugInfo = 0;
    PerfLib::CriticalSection::CriticalSection((PerfLib::CriticalSection*)&this[8].LockCount);
    LOBYTE(this[9].RecursionCount) = 0;
    PerfLib::CriticalSection::Initialize((struct _RTL_CRITICAL_SECTION*)((char*)this + 196), 0);
    LOBYTE(this[9].OwningThread) = 0;
    return this;
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

LPTOP_LEVEL_EXCEPTION_FILTER __stdcall sub_42EEE0(int a1, int a2)
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

char Buffer[100]; // Búfer para almacenar la cadena formateada
CHAR DisplayName[512];
CHAR ServiceStartName[128];
CHAR ReturnedString;


int main(int argc, const char** argv, const char** envp)
{
    char v3; // bl
    int v5; // [esp+0h] [ebp-220h] BYREF
    SERVICE_TABLE_ENTRYA ServiceStartTable; // [esp+4h] [ebp-21Ch] BYREF
    int v7; // [esp+Ch] [ebp-214h]
    int v8; // [esp+10h] [ebp-210h]
    CHAR ReturnedString[8]; // [esp+14h] [ebp-20Ch] BYREF
    CHAR v10[512]; // [esp+1Ch] [ebp-204h] BYREF
     
     
    if (!sub_42EA70()) return;

    if ((unsigned __int8)CheckStringConfig("Server", "ServerId", ReturnedString, 8u))
    {
        v5 = 0;
        if ((unsigned __int8)CheckIntConfig("Server", "Port", (int)&v5))
        {
            if ((unsigned __int8)CheckStringConfig("Service", "Name", v10, 0x200u))
            {
                sprintf(Buffer, "%s [%s]", v10, ReturnedString);
                if ((unsigned __int8)CheckStringConfig("Service", "DisplayName", v10, 0x200u))
                {
                    sprintf(DisplayName, "%s %u [%s]", v10, v5, ReturnedString);
                    if ((unsigned __int8)CheckStringConfig("Service", "ExecUser", v10, 0x200u))
                        sprintf(ServiceStartName, ".\\%s", v10);
                    else
                        ServiceStartName[0] = 0;
                    if (!(unsigned __int8)CheckStringConfig("Service", "ExecPassword", &::ReturnedString, 0x80u))
                        ::ReturnedString = 0;
                    if (argc > 1)
                    {
                        if (!_stricmp(argv[1], "-install"))
                        {
                            InstallServer();
                        }
                        else if (!_stricmp(argv[1], "-remove"))
                        {
                            RemoveServer();
                        }
                        else if (!_stricmp(argv[1], "-start"))
                        {
                            StartServer();
                        }
                        else if (!_stricmp(argv[1], "-stop"))
                        {
                            StopServer();
                        }
                    }
                    ServiceStartTable.lpServiceName = Buffer;
                    ServiceStartTable.lpServiceProc = (LPSERVICE_MAIN_FUNCTIONA)sub_42EEE0;
                    v7 = 0;
                    v8 = 0;
                    if (argc < 2)
                        StartServiceCtrlDispatcherA(&ServiceStartTable);
                    return 0;
                }
                else
                {
                    Console_Log("[RW] Failed to read property (DisplayName)");
                    return 1;
                }
            }
            else
            {
                Console_Log("[RW] Failed to read property (Name)", v3);
                return 1;
            }
        }
        else
        {
            Console_Log("[RW] Failed to read property (Port)", v3);
            return 1;
        }
    }
    else
    {
        Console_Log("[RW] Failed to read property (ServerId)", v5);
        return 1;
    }
}