#include <stdio.h>
#include <string.h>
#include "PluginInfo.h"
#include "Error.h"

#define TEMP_BUFFER_SIZE (200)

std::string PluginInfo::Serialize(void){
	std::string ret= "PLUGIN_INFO";
	ret+= '\n';
	
	ret+= "id=";
	ret+= id;
	ret+= '\n';
	
	ret+= "instanceName=";
	ret+= instanceName;
	ret+= '\n';
	
	ret+= "privateCloud=";
	ret+= privateCloud;
	ret+= '\n';
	
	ret+= "host=";
	ret+= host.adderss;
	ret+= ':';
	ret += host.port;
	ret+= '\n';
	
	ret+= "upTime=";
	ret+= upTime;
	ret+= '\n';
	
	ret+= "latency=";
	ret+= latency;
	ret+= '\n';
	
	ret+= "costPerGiga=";
	ret+= costPerGiga;
	ret+= '\n';
	
	ret+= "timestamp=";
	ret+= timestamp;
	ret+= '\n';
	
	ret+= "numCores=";
	ret+= numCores;
	ret+= '\n';
	
	ret+= "numNodes=";
	ret+= numNodes;
	ret+= '\n';
	
	ret+= "numOccupied=";
	ret+= numOccupied;
	ret+= '\n';
	
	ret+= "ranking=";
	ret+= ranking;
	ret+= '\n';
	
	ret+= "fsSize=";
	ret+= fsSize;
	ret+= '\n';
	
	ret+= "memoryTotal=";
	ret+= memoryTotal;
	ret+= '\n';
	
	ret+= "memoryFree=";
	ret+= memoryFree;
	ret+= '\n';
	
	ret+= "currentFrequencyCore=";
	ret+= currentFrequencyCore;
	ret+= '\n';
	
	ret+= "costPerHour=";
	ret+= costPerHour;
	ret+= '\n';
	
	ret+= "bandwith=";
	ret+= bandwith;
	ret+= '\n';
	
	ret+= "ip=";
	ret+= ip;
	ret+= '\n';
	
	ret+= "provider=";//obs:: n pode ter \n no provider
	ret+= provider;
	ret+= '\n';
	
	//adições para suporte de GPU
	ret+= "gpuMemoryTotal=";
	ret+= gpuMemoryTotal;
	ret+= '\n';
	
	ret+= "gpuMemoryMaxFrequency=";
	ret+= gpuMemoryMaxFrequency;
	ret+= '\n';
	
	ret+= "gpuMemoryBus=";
	ret+= gpuMemoryBus;
	ret+= '\n';
	
	ret+= "gpuMemoryBandwith=";
	ret+= gpuMemoryBandwith;
	ret+= '\n';
	
	ret+= "gpuFloatingPointPerf=";
	ret+= gpuFloatingPointPerf;
	ret+= '\n';
	
	ret+= "gpuMaxFrequency=";
	ret+= gpuMaxFrequency;
	ret+= '\n';
	
	return ret;
}


PluginInfo::PluginInfo(std::string const &str){
/*
	char tempID[TEMP_BUFFER_SIZE], tempInstanceName[TEMP_BUFFER_SIZE], 
	int res= sscanf(
				str.c_str(),
				"PLUGIN_INFO id=%s instanceName=%s privateCloud=%d host=%[^:]:%d upTime=%ld latency=%lf costPerGiga=%lf timestamp=%ld numCores=%d numNodes=%d numOccupied=%d ranking=%lf fsSize=%f memoryTotal=%lf memoryFree=%lf currentFrequencyCore=%lf costPerHour=%lf bandwith=%lf ip=%s provider=%s gpuMemoryTotal=%lf gpuMemoryMaxFrequency=%lf gpuMemoryBus=%lf gpuMemoryBandwith=%lf gpuFloatingPointPerf%lf gpuMaxFrequency=%lf"
				
				);
*/
	int size= str.length();
	char *temp= (char*)operator new[] (size+1);
	memcpy(temp, str.c_str(), size);
	temp[size]= '\0';
	
	char delimiter[2];
	delimiter[0]= '\n';
	delimiter[1]= '\0';
	ASSERT(0 == memcmp("PLUGIN_INFO" , strtok(temp, delimiter), STRLEN("PLUGIN_INFO") ) );
	char *token, buffer[TEMP_BUFFER_SIZE+1];
	buffer[TEMP_BUFFER_SIZE]= '\0';
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "id=%[^\n]", buffer) );
	id= buffer;
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "instanceName=%[^\n]", buffer) );
	instanceName= buffer;
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "privateCloud=%d", &privateCloud) );
	
	token= strtok(NULL, delimiter);
	ASSERT(2 == sscanf(token, "instanceName=%[^:]:%d", buffer, &(host.port) ) );
	host.adderss= buffer;
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "upTime=%ld", &upTime) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "latency=%lf", &latency) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "costPerGiga=%lf", &costPerGiga) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "timestamp=%ld", &timestamp) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "numCores=%d", &numCores) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "numNodes=%d", &numNodes) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "numOccupied=%d", &numOccupied) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "ranking=%lf", &ranking) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "fsSize=%f", &fsSize) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "memoryTotal=%lf", &memoryTotal) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "memoryFree=%lf", &memoryFree) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "currentFrequencyCore=%lf", &currentFrequencyCore) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "costPerHour=%lf", &costPerHour) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "bandwith=%lf", &bandwith) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "ip=%[^\n]", buffer) );
	ip= buffer;
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "provider=%[^\n]", buffer) );
	provider= buffer;
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "gpuMemoryTotal=%lf", &gpuMemoryTotal) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "gpuMemoryMaxFrequency=%lf", &gpuMemoryMaxFrequency) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "gpuMemoryBus=%lf", &gpuMemoryBus) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "gpuMemoryBandwith=%lf", &gpuMemoryBandwith) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "gpuFloatingPointPerf=%lf", &gpuFloatingPointPerf) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "gpuMaxFrequency=%lf", &gpuMaxFrequency) );
	
	operator delete[](temp);
	
}

