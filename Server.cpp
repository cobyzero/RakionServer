#include "Main.h"
 
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
