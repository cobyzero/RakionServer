#pragma once
#include "IPv4Address.h"

namespace PerfLib {

	class TcpSocket
	{
	public:
		TcpSocket();
		int Initialize(bool a2);
		int SetNonBlocking(BOOL argp);
		int Close(int optval);
		int Connect(const PerfLib::IPv4Address* name);
		int Listen(int backlog);
		bool Accept(PerfLib::TcpSocket* a2, void* a3, unsigned int a4, unsigned int* a5, _OVERLAPPED* a6);
		void GetAcceptedSocketAddress(void* a2, unsigned int a3, PerfLib::IPv4Address* a4, PerfLib::IPv4Address* a5);
		int Send(const char* a2, int a3, LPDWORD lpNumberOfBytesSent, _OVERLAPPED* lpOverlapped);
		int Recv(DWORD Flags, int a3, LPDWORD lpNumberOfBytesRecvd, _OVERLAPPED* lpOverlapped);
		int DuplicateProperties(const PerfLib::TcpSocket* optval);

	};


}
