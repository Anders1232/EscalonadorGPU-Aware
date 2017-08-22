#include "Comunicador.hpp"

#include <net/if.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

Comunicador::Comunicador(int port, int64_t handShakeMsg)
{
	
	
	java.sin6_addr.in6_addr= in6addr_loopback;
	java.sin6_family= AF_INET6;
//	java.sin6_flowinfo;
	java.sin6_port= htons(port);
	java.sin6_scope_id= if_nametoindex("lo");//loopback, ver se esse nome é padronizado
	
/*
	const addrinfo addrHint;
	addrHint.ai_family= PF_INET6;
	addrHint.ai_socktype= SOCK_DGRAM;
	addrHint.ai_protocol= IPPROTO_UDP;
	getaddrinfo("localhost", , addrHint, );
*/
	socketFD= socket(AF_INET6, SOCK_DGRAM, 0);
	if (socketFD < 0)
	{
		Error("[ERROR] Fail opening socket\n");
	}
	
/*	int myPort= (rand()%64000)+1024;
	me.sin6_addr= in6addr_loopback;
	me.sin6_family= AF_INET6;
	me.sin6_port= htons(myPort);
	me.sin6_scope_id= if_nametoindex("lo");//supondo que o loopback sempre é a interface 1.
	int result= bind(socketFD, me, sizeof(sockaddr_in6));
	if(result)
	{
		switch(errno)
		{
			case(EACCES):
			{
				printf("The address is protected, and the user is not the superuser.\n");
				break;
			}
			case(EADDRINUSE):
			{
				printf("The given address is already in use.\n");
				break;
			}
			case(EBADF):
			{
				printf("sockfd is not a valid descriptor.\n");
				break;
			}
			case(EINVAL):
			{
				printf("The socket is already bound to an address.\n");
				break;
			}
			case(ENOTSOCK):
			{
				printf("sockfd is a descriptor for a file, not a socket.\n");
				break;
			}
		}
		throw(std::string("[ERROR] Cound not bind local socket\n"));
	}
	*/
	
	buffer = new char[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE*sizeof(char));
	sprintf(buffer, "%ld", handShakeMsg);
	int bytesReadOrWritten= sendto(socketFD, buffer, strlen(buffer), java, sizeof(sockaddr_in6));
	if(bytesReadOrWritten < 0)
	{
		Error("[ERROR] Error writing to socket\n");
	}
	int recievedSocketLenght= sizeof(SocketAddress);
	SocketAddress recievedSocket;
	bytesReadOrWritten= recvfrom(socketFD, buffer, BUFFER_SIZE, 0, (struct sockaddr*) &recievedSocket, &recievedSocketLenght);
	if (bytesReadOrWritten < 0)
	{
		Error("[ERROR] Error reading from socket\n");
	}
	if(recievedSocket.sin6_port != java.sin6_port)
	{
		Error("Expected msg from the same port we sent to");
	}
	if(strcmp("Ack!", buffer))
	{
		Error("HandShake Failed!");
	}
}
