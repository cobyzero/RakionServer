#include "main.h"
#include "IPv4Address.h"

PerfLib::IPv4Address::IPv4Address()
{
	for (size_t i = 0; i < 4; i++)
	{
		a[i] = 0;
	}
}

PerfLib::IPv4Address::IPv4Address(const char* cp, unsigned short hostshort) {

	for (size_t i = 0; i < 4; i++)
	{
		a[i] = 0;
	} 

	a[1] = inet_addr(cp);
	b1 = 2;
	port = htons(hostshort);
} 

PerfLib::IPv4Address::~IPv4Address() {
}

const struct sockaddr_in* PerfLib::IPv4Address::GetSockAddr() {
	return (const struct sockaddr_in*)this;
}

struct sockaddr_in* PerfLib::IPv4Address::CopySockAddress(struct sockaddr_in* retstr) {
	struct sockaddr_in* result; // eax

	result = retstr;
	*retstr = *(struct sockaddr_in*)this;
	return result;
}

int PerfLib::IPv4Address::GetSize()
{
	return 0x10;
}


char* PerfLib::IPv4Address::GetIPAddress() {
	return inet_ntoa(*(ipAddress));
}

int PerfLib::IPv4Address::GetPort() {
	return ntohs(port);
}

