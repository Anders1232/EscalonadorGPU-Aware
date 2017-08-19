#include "Comunicador.hpp"

#include <net/if.h>
#include <netdb.h>

Comunicador::Comunicador(int port)
{
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[0]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[1]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[2]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[3]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[4]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[5]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[6]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[7]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[8]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[9]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[10]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[11]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[12]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[13]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[14]=0;
	other.sin6_addr.in6_addr.__in6_u.__u6_addr8[15]=1;
	other.sin6_family= AF_INET6;
//	other.sin6_flowinfo;
	other.sin6_port= htons(port);
	other.sin6_scope_id= if_nametoindex("lo");//loopback, ver se esse nome é padronizado
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
	
	char *helloMsg= "Hello?";
	
}
