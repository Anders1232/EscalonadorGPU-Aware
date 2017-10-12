#include "Comunicador.hpp"

#include <string>
#include <vector>
#include <net/if.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

#include <thread>
#include <pthread.h>

#include "Error.h"
#include "SimpleRatingSched.h"

#define BIONIMBUZ_PREFIX_SCHED "[BioNimbuZ]SCHED="
#define BIONIMBUZ_SCHED_SIMPLE_RATING_SCHED "[BioNimbuZ]SIMPLE_RATING_SCHED"
#define BIONIMBUZ_UNKNOWN_SCHED "[BioNimbuZ]UNKNOWN_SCHED"
#define BIONIMBUZ_STATUS_OK "[BioNimbuZ]STATUS_OK"
#define BIONIMBUZ_SCHED_DEFINED "[BioNimbuZ]SSCHEDULER_DEFINED"

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
	bytesReadOrWritten= sendto(socketFD, buffer, strlen(buffer), 0, (struct sockaddr*)&java, sizeof(sockaddr_in6));
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
	
	DefineSched();
}

std::string Comunicador::Receive(std::string begin)
{
	uint recievedSocketLenght= sizeof(sockaddr_storage);
	sockaddr_storage recievedSocket;
	do{
		memset(buffer, '\0', BUFFER_SIZE);
		bytesReadOrWritten= recvfrom(socketFD, buffer, BUFFER_SIZE, 0, (struct sockaddr*) &recievedSocket, &recievedSocketLenght);
		ASSERT(bytesReadOrWritten>0);
		if( ( ( (SocketAddress*)&recievedSocket) )->sin6_port != java.sin6_port){
			std::cout<< "Received message from wrong origin, ignoring it. Message: "<< buffer;
		}
		if(NULL == strstr(buffer, begin.c_str())){
			std::cout<< "Received invalid message, ignoring it. Message: "<< buffer;
		}
		else{
			break;
		}
	}
	while(1);
	return buffer;
}


void Comunicador::DefineSched(void){
	bool success= false;
	do{
		std::string msg= Receive(BIONIMBUZ_PREFIX_SCHED);
		if(std::string::npos != msg.find(BIONIMBUZ_SCHED_SIMPLE_RATING_SCHED)){
			sched= new SimpleRatingSched();
			success=true;
			bytesReadOrWritten= sendto(socketFD, BIONIMBUZ_SCHED_DEFINED, STRLEN(BIONIMBUZ_SCHED_DEFINED), 0, (struct sockaddr*)&java, sizeof(sockaddr_in6));
		}
		else{
			bytesReadOrWritten= sendto(socketFD, BIONIMBUZ_UNKNOWN_SCHED, STRLEN(BIONIMBUZ_UNKNOWN_SCHED), 0, (struct sockaddr*)&java, sizeof(sockaddr_in6));
			ASSERT2(bytesReadOrWritten > 0, "[ERROR] Error writing to socket\n");
		}
	}
	while(!success);
}

class StringForPluginInfo{
	public:
		std::unordered_map<std::string, PluginInfo>* map;
		pthread_mutex_t *mutex;
		std::string strToProcess;
		
		StringForPluginInfo(
				std::unordered_map<std::string, PluginInfo>* map,
				pthread_mutex_t *mutex,
				std::string strToProcess
				):
			map(map),
			mutex(mutex),
			strToProcess(strToProcess){}
};

class StringForJob{
	public:
		std::vector<Job>* jobs;
		pthread_mutex_t *mutex;
		std::string strToProcess;
		StringForJob(
				std::vector<Job>* jobs,
				pthread_mutex_t *mutex,
				std::string strToProcess
				):
			jobs(jobs),
			mutex(mutex),
			strToProcess(strToProcess){}
};

void* CreateJob(void*)

void Comunicador::Schedule(void){
	int size= BUFFER_SIZE;
/*	char *temp= (char*)operator new[] (size+1);
	memcpy(temp, str.c_str(), size);
	temp[size]= '\0';
*/	
	char delimiter[2];
	delimiter[0]= '\r';
	delimiter[1]= '\0';
	char *token;
	ASSERT(0 == memcmp("SCHEDULE" , token= strtok(buffer, delimiter), STRLEN("SCHEDULE") ) );
//	buffer[TEMP_BUFFER_SIZE]= '\0';
	
	std::vector<std::string> jobList;
	int vecSize;
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "JOBS=%d", &vecSize) );
	jobList.reserve(vecsize);
	REPORT_DEBUG("token= " << token << "\n");
	for(int i=0; i < vecSize; i++){
		token= strtok(NULL, delimiter);
		REPORT_DEBUG("token= " << token << "\n");
		ASSERT(1 == sscanf(token, "%[^\n]", buffer) );
		jobList.emplace_back(token);
	}
	
	pthread_t *threads= operator new[] (jobList.size());
	for(int i=0; i< vecSize. i++){
		
		pthread_create()
	}
}

