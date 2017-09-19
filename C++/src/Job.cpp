#include <string.h>
#include <stdio.h>
#include "Job.h"
#include "Error.h"

#define TEMP_BUFFER_SIZE (200)

std::string Job::Serialize(){
	std::string ret= "JOB";
	ret+= '\n';
	
	ret+= "id=";
	ret+= id;
	ret+= '\n';
	
	ret+= "testId=";
	ret+= testId;
	ret+= '\n';
	
	ret+= "localID=";
	ret+= testId;
	ret+= '\n';
	
	ret+= "serviceId=";
	ret+= serviceId;
	ret+= '\n';
	
	ret+= "args=";
	ret+= args;
	ret+= '\n';
	
	ret+= "ipJob=";
	ret+= ipJob.size();
	for(uint i=0; i < ipJob.size(); i++){
		ret+= '>';
		ret+= ipJob[i];
	}
	
	ret+= "inputURL=";
	ret+= inputURL;
	ret+= '\n';
	
	ret+= "outputs=";
	ret+= outputs.size();
	for(uint i=0; i < outputs.size(); i++){
		ret+= '>';
		ret+= outputs[i];
	}
	
	ret+= "timestamp=";
	ret+= timestamp;
	ret+= '\n';
	
	ret+= "worstExecution=";
	ret+= worstExecution;
	ret+= '\n';
	
	ret+= "dependecies=";
	ret+= dependecies.size();
	for(uint i=0; i < dependecies.size(); i++){
		ret+= '>';
		ret+= dependecies[i];
	}
	
	ret+= "referenceFile=";
	ret+= referenceFile;
	ret+= '\n';
	
	ret+= "useGPU=";
	ret+= useGPU?"true":"false";
	ret+= '\n';
	
	ret+= "useCPU=";
	ret+= useCPU?"true":"false";
	ret+= '\n';
	
	ret+= "gpuPref=";
	ret+= gpuPref;
	ret+= '\n';
	
	return ret;
}

Job::Job(std::string const &str){
	int size= str.length();
	char *temp= (char*)operator new[] (size+1);
	memcpy(temp, str.c_str(), size);
	temp[size]= '\0';
	
	char delimiter[2];
	delimiter[0]= '\n';
	delimiter[1]= '\0';
	ASSERT(0 == memcmp("JOB" , strtok(temp, delimiter), STRLEN("JOB") ) );
	char *token, buffer[TEMP_BUFFER_SIZE+1];
	buffer[TEMP_BUFFER_SIZE]= '\0';
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "id=%[^\n]", buffer) );
	id= buffer;
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "testId=%ld", &testId) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "localID=%[^\n]", buffer) );
	localID= buffer;
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "serviceId=%[^\n]", buffer) );
	serviceId= buffer;
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "args=%[^\n]", buffer) );
	args= buffer;
	
	int vecSize;
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "ipJob=%d>", &vecSize) );
	ipJob.resize(vecSize);
	for(int i=0; i < vecSize; i++){
		token= strtok(NULL, ">\n");
		ASSERT(1 == sscanf(token, "%[^\n]", buffer) );
		ipJob[i]= buffer;
	}
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "inputURL=%[^\n]", buffer) );
	inputURL= buffer;
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "outputs=%d>", &vecSize) );
	outputs.resize(vecSize);
	for(int i=0; i < vecSize; i++){
		token= strtok(NULL, ">\n");
		ASSERT(1 == sscanf(token, "%[^\n]", buffer) );
		outputs[i]= buffer;
	}
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "timestamp=%ld", &timestamp) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "worstExecution=%lf", &worstExecution) );
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "dependecies=%d>", &vecSize) );
	dependecies.resize(vecSize);
	for(int i=0; i < vecSize; i++){
		token= strtok(NULL, ">\n");
		ASSERT(1 == sscanf(token, "%[^\n]", buffer) );
		dependecies[i]= buffer;
	}
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "referenceFile=%[^\n]", buffer) );
	referenceFile= buffer;
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "useGPU=%[^\n]", buffer) );
	useCPU= !strcmp(buffer, "true");
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "useCPU=%[^\n]", buffer) );
	useCPU= !strcmp(buffer, "true");
	
	token= strtok(NULL, delimiter);
	ASSERT(1 == sscanf(token, "gpuPref=%f", &gpuPref) );
	
	operator delete[](temp);
}

