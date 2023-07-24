#pragma once
 
namespace PerfLib {

	struct IPv4Address
	{
		unsigned int miembro1;
		unsigned int miembro2;
		unsigned int miembro3;
		unsigned int miembro4;
	public:
		IPv4Address();
		IPv4Address(const char* cp, unsigned short hostshort);
		IPv4Address(const IPv4Address& other);
		~IPv4Address();

		const struct sockaddr_in* GetSockAddr();

		sockaddr_in* CopySockAddress(sockaddr_in* retstr);

		char* GetIPAddress(in_addr* ipAddress);
		int GetPort();



	};

}

