#include "main.h"
#include "IPv4Address.h"

PerfLib::IPv4Address::IPv4Address()
{
    miembro1 = 0;
    miembro2 = 0;
    miembro3 = 0;
    miembro4 = 0;
}
 
PerfLib::IPv4Address:: IPv4Address(const char* cp, unsigned short hostshort) {
    miembro1 = inet_addr(cp);
    miembro2 = 0;
    miembro3 = htons(hostshort);
    miembro4 = 0x0002; // Valor hexadecimal de 2 (0x0002)
}

PerfLib::IPv4Address::IPv4Address(const IPv4Address& other) {
    miembro1 = other.miembro1;
    miembro2 = other.miembro2;
    miembro3 = other.miembro3;
    miembro4 = other.miembro4;
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


char* PerfLib::IPv4Address::GetIPAddress(struct in_addr* ipAddress) {
    return inet_ntoa(*ipAddress);
}

int PerfLib::IPv4Address::GetPort() {
    return ntohs(miembro2);
}

