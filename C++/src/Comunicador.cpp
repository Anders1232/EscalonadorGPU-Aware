#include "Comunicador.hpp"

#include <net/if.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

#include "Error.h"

Comunicador::Comunicador(int port, int64_t handShakeMsg)
{
	TEMP_REPORT_I_WAS_HERE;
	
	java.sin6_addr= in6addr_loopback;
	java.sin6_family= AF_INET6;
	java.sin6_port= htons(port);
	java.sin6_scope_id= if_nametoindex("lo");//loopback, ver se esse nome é padronizado
	TEMP_REPORT_I_WAS_HERE;
	if(0 == java.sin6_scope_id)
	{
		Error("Could not find the loopBackInterface.");
	}
	
	socketFD= socket(AF_INET6, SOCK_DGRAM, 0);
	TEMP_REPORT_I_WAS_HERE;
	if (socketFD < 0)
	{
		Error("[ERROR] Fail opening socket\n");
	}
	
	buffer = new char[BUFFER_SIZE];		//desalocar no destrutor
	memset(buffer, 0, BUFFER_SIZE*sizeof(char));
	sprintf(buffer, "%ld", handShakeMsg);
	TEMP_REPORT_I_WAS_HERE;
	int bytesReadOrWritten= sendto(socketFD, buffer, strlen(buffer), 0, (struct sockaddr*)&java, sizeof(sockaddr_in6));
	TEMP_REPORT_I_WAS_HERE;
	if(bytesReadOrWritten < 0)
	{
		Error("[ERROR] Error writing to socket\n");
	}
	uint recievedSocketLenght= sizeof(sockaddr_storage);
	sockaddr_storage recievedSocket;
	TEMP_REPORT_I_WAS_HERE;
	bytesReadOrWritten= recvfrom(socketFD, buffer, BUFFER_SIZE, 0, (struct sockaddr*) &recievedSocket, &recievedSocketLenght);
	TEMP_REPORT_I_WAS_HERE;
	if (bytesReadOrWritten < 0)
	{
		Error("[ERROR] Error reading from socket\n");
	}
	if( ( ( (SocketAddress*)&recievedSocket) )->sin6_port != java.sin6_port)
	{
		Error("Expected msg from the same port we sent to");
	}
	if(strcmp("Ack!", buffer))
	{
		Error("HandShake Failed!");
	}
	TEMP_REPORT_I_WAS_HERE;
	printf("Handshake sucess!");
	
	
}
