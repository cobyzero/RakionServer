#include "main.h"
#include "TcpSocket.h"
#include "IPv4Address.h"

PerfLib::TcpSocket::TcpSocket()
{
	*(DWORD*)this = -1;
	*((BYTE*)this + 4) = 0;
	*((DWORD*)this + 2) = 0;
	*((DWORD*)this + 3) = 0;
}

int PerfLib::TcpSocket::Initialize(bool a2)
{
	SOCKET v3; // eax

	v3 = WSASocketA(2, 1, 6, 0, 0, a2);
	*(DWORD*)this = v3;
	if (v3 == -1)
		return WSAGetLastError();
	else
		return 0;
}

int PerfLib::TcpSocket::SetNonBlocking(BOOL argp)
{
	argp = argp;
	if (ioctlsocket(*(DWORD*)this, -2147195266, (u_long*)&argp) == -1)
		return WSAGetLastError();
	else
		return 0;
}

int PerfLib::TcpSocket::Close(int optval)
{
	int result; // eax

	result = *(DWORD*)this;
	if (*(DWORD*)this != -1)
	{
		if ((BYTE)optval)
		{
			optval = 1;
			setsockopt(result, 0xFFFF, -129, (const char*)&optval, 4);
		}
		else
		{
			shutdown(result, 1);
		}
		result = closesocket(*(DWORD*)this);
		*(DWORD*)this = -1;
	}
	return result;
}

int PerfLib::TcpSocket::Connect(const struct PerfLib::IPv4Address* name)
{
	return connect(*(DWORD*)this, (const struct sockaddr*)name, 16);
}

int PerfLib::TcpSocket::Listen(int backlog)
{
	return listen(*(DWORD*)this, backlog);
}

bool PerfLib::TcpSocket::Accept(
	struct PerfLib::TcpSocket* a2,
	void* a3,
	unsigned int a4,
	unsigned int* a5,
	struct _OVERLAPPED* a6)
{
	char* v7; // edi
	SOCKET v9; // [esp-20h] [ebp-44h]
	DWORD cbBytesReturned; // [esp+Ch] [ebp-18h] BYREF
	int vInBuffer; // [esp+10h] [ebp-14h] BYREF
	__int16 v12; // [esp+14h] [ebp-10h]
	__int16 v13; // [esp+16h] [ebp-Eh]
	char v14; // [esp+18h] [ebp-Ch]
	char v15; // [esp+19h] [ebp-Bh]
	char v16; // [esp+1Ah] [ebp-Ah]
	char v17; // [esp+1Bh] [ebp-9h]
	char v18; // [esp+1Ch] [ebp-8h]
	char v19; // [esp+1Dh] [ebp-7h]
	char v20; // [esp+1Eh] [ebp-6h]
	char v21; // [esp+1Fh] [ebp-5h]
	int v22; // [esp+20h] [ebp-4h]

	v7 = (char*)this + 8;
	v22 = dword_454928;
	if (*((DWORD*)this + 2))
		return (*(int(__stdcall**)(DWORD, DWORD, void*, unsigned int, int, int, unsigned int*, struct _OVERLAPPED*))v7)(
			*(DWORD*)this,
			*(DWORD*)a2,
			a3,
			a4 - 64,
			32,
			32,
			a5,
			a6) == 1;
	v9 = *(DWORD*)this;
	vInBuffer = -1254720015;
	v12 = -13396;
	v13 = 4559;
	v14 = -107;
	v15 = -54;
	v16 = 0;
	v17 = 0x80;
	v18 = 95;
	v19 = 72;
	v20 = -95;
	v21 = -110;
	return WSAIoctl(v9, 0xC8000006, &vInBuffer, 0x10u, (char*)this + 8, 4u, &cbBytesReturned, 0, 0) != -1
		&& (*(int(__stdcall**)(DWORD, DWORD, void*, unsigned int, int, int, unsigned int*, struct _OVERLAPPED*))v7)(
			*(DWORD*)this,
			*(DWORD*)a2,
			a3,
			a4 - 64,
			32,
			32,
			a5,
			a6) == 1;
}

void PerfLib::TcpSocket::GetAcceptedSocketAddress(
	void* a2,
	unsigned int a3,
	struct PerfLib::IPv4Address* a4,
	struct PerfLib::IPv4Address* a5)
{
	char* v5; // esi
	SOCKET v6; // [esp-8h] [ebp-50h]
	PerfLib::IPv4Address* v7; // [esp+20h] [ebp-28h] BYREF
	PerfLib::IPv4Address* v8; // [esp+24h] [ebp-24h] BYREF
	DWORD cbBytesReturned; // [esp+28h] [ebp-20h] BYREF
	char v10[4]; // [esp+2Ch] [ebp-1Ch] BYREF
	char v11[4]; // [esp+30h] [ebp-18h] BYREF
	int vInBuffer[2]; // [esp+34h] [ebp-14h] BYREF
	char v13; // [esp+3Ch] [ebp-Ch]
	char v14; // [esp+3Dh] [ebp-Bh]
	char v15; // [esp+3Eh] [ebp-Ah]
	char v16; // [esp+3Fh] [ebp-9h]
	char v17; // [esp+40h] [ebp-8h]
	char v18; // [esp+41h] [ebp-7h]
	char v19; // [esp+42h] [ebp-6h]
	char v20; // [esp+43h] [ebp-5h]
	int v21; // [esp+44h] [ebp-4h]

	v5 = (char*)this + 12;
	v21 = dword_454928;
	if (*((DWORD*)this + 3))
		goto LABEL_3;
	v6 = *(DWORD*)this;
	vInBuffer[0] = -1254720014;
	vInBuffer[1] = 298830764;
	v13 = -107;
	v14 = -54;
	v15 = 0;
	v16 = 0x80;
	v17 = 95;
	v18 = 72;
	v19 = -95;
	v20 = -110;
	if (WSAIoctl(v6, 0xC8000006, vInBuffer, 0x10u, (char*)this + 12, 4u, &cbBytesReturned, 0, 0) != -1)
	{
	LABEL_3:
		(*(void(__stdcall**)(void*, unsigned int, int, int, PerfLib::IPv4Address**, char*, PerfLib::IPv4Address**, char*))v5)(
			a2,
			a3 - 64,
			32,
			32,
			&v7,
			v10,
			&v8,
			v11);
		a4 = v7;
		a5 = v8;
	}
}

int PerfLib::TcpSocket::Send(
	const char* a2,
	int a3,
	LPDWORD lpNumberOfBytesSent,
	struct _OVERLAPPED* lpOverlapped)
{
	SOCKET v5; // ecx
	struct _WSABUF Buffers; // [esp+0h] [ebp-8h] BYREF

	v5 = *(DWORD*)this;
	Buffers.buf = (CHAR*)a2;
	Buffers.len = a3;
	return WSASend(v5, &Buffers, 1u, lpNumberOfBytesSent, 0, lpOverlapped, 0);
}

int PerfLib::TcpSocket::Recv(
	DWORD Flags,
	int a3,
	LPDWORD lpNumberOfBytesRecvd,
	struct _OVERLAPPED* lpOverlapped)
{
	SOCKET v6; // [esp-1Ch] [ebp-24h]
	struct _WSABUF Buffers; // [esp+0h] [ebp-8h] BYREF

	Buffers.buf = (CHAR*)Flags;
	Buffers.len = a3;
	v6 = *(DWORD*)this;
	Flags = 0;
	return WSARecv(v6, &Buffers, 1u, lpNumberOfBytesRecvd, &Flags, lpOverlapped, 0);
}

int PerfLib::TcpSocket::DuplicateProperties(
	const struct PerfLib::TcpSocket* optval)
{
	SOCKET v3; // [esp-14h] [ebp-14h]

	v3 = *(DWORD*)this;
	optval = *(const struct PerfLib::TcpSocket**)optval;
	return setsockopt(v3, 0xFFFF, 28683, (const char*)&optval, 4);
}