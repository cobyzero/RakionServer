#pragma once

#include <iostream>
//#include <winsvc.h>
#include <Windows.h>
#include <WinSock2.h> 
#include "IPv4Address.h"   
#include "TcpSocket.h"
#include <Dbghelp.h> 
#include "Server.h"
#include "ServiceServer.h"

DWORD dword_456D84;
DWORD dword_454928; //checar
char Buffer[100]; // Búfer para almacenar la cadena formateada
CHAR DisplayName[512];
CHAR ServiceStartName[128];
CHAR ReturnedString;

struct _SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hServiceStatus;
void* Block;