#pragma once

namespace PerfLib {

	class IPv4Address
	{
		DWORD* a;

		WORD b1;
		WORD port;

		in_addr* ipAddress;
	public:
		IPv4Address();
		IPv4Address(const char* cp, unsigned short hostshort);
		~IPv4Address();

		const struct sockaddr_in* GetSockAddr();

		sockaddr_in* CopySockAddress(sockaddr_in* retstr);

		int GetSize();

		char* GetIPAddress();
		int GetPort();

		IPv4Address& operator=(const IPv4Address& other) {
			if (this != &other) {
				for (int i = 0; i < 4; ++i) {
					a[i] = other.a[i];
				}
			}
			return *this;
		} 
	};

}

