#ifndef HOST_H
#define HOST_H

#include <string>

class Host
{
	public:
		std::string adderss;
		int port;
		Host(std::string address, int port);
};

#endif // HOST_H
