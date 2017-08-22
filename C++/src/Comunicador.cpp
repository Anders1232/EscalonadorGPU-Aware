#include "Comunicador.hpp"

#include <net/if.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

Comunicador::Comunicador(int port, int64_t handShakeMsg)
{
	
	
	java.sin6_addr.in6_addr= in6addr_loopback;
	java.sin6_family= AF_INET6;
	java.sin6_port= htons(port);
	java.sin6_scope_id= if_nametoindex("lo");//loopback, ver se esse nome é padronizado
	if(0 == java.sin6_scope_i)
	{
		Error("Could not find the loopBackInterface.");
	}
	
	socketFD= socket(AF_INET6, SOCK_DGRAM, 0);
	if (socketFD < 0)
	{
		Error("[ERROR] Fail opening socket\n");
	}
	
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
