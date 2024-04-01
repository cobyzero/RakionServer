#include "main.h" 



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

 

struct _RTL_CRITICAL_SECTION* sub_42A6E0()
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
                    ServiceStartTable.lpServiceProc = (LPSERVICE_MAIN_FUNCTIONA)ServiceProc;
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