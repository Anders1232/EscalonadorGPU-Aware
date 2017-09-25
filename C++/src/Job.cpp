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
	ret+= std::to_string(testId);
	ret+= '\n';
	
	ret+= "localID=";
	ret+= localID;
	ret+= '\n';
	
	ret+= "serviceId=";
	ret+= serviceId;
	ret+= '\n';
	
	ret+= "args=";
	ret+= args;
	ret+= '\n';
	
	ret+= "ipJob=";
	ret+= std::to_string(ipJob.size() );
	for(uint i=0; i < ipJob.size(); i++){
		ret+= '>';
		ret+= ipJob[i];
	}
	
	ret+= "\ninputURL=";
	ret+= inputURL;
	ret+= '\n';
	
	ret+= "outputs=";
	ret+= std::to_string(outputs.size() );
	for(uint i=0; i < outputs.size(); i++){
		ret+= '>';
		ret+= outputs[i];
	}
	
	ret+= "\ntimestamp=";
	ret+= std::to_string(timestamp);
	ret+= '\n';
	
	ret+= "worstExecution=";
	ret+= std::to_string(worstExecution);
	ret+= '\n';
	
	ret+= "dependecies=";
	ret+= std::to_string(dependecies.size() );
	for(uint i=0; i < dependecies.size(); i++){
		ret+= '>';
		ret+= dependecies[i];
	}
	
	ret+= "\nreferenceFile=";
	ret+= referenceFile;
	ret+= '\n';
	
	ret+= "useGPU=";
	ret+= useGPU?"true":"false";
	ret+= '\n';
	
	ret+= "useCPU=";
	ret+= useCPU?"true":"false";
	ret+= '\n';
	
	ret+= "gpuPref=";
	ret+= std::to_string(gpuPref);
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
	token= strtok(NULL, ">\n");
	ASSERT(1 == sscanf(token, "ipJob=%d>", &vecSize) );
#ifdef DEBUG
	REPORT_DEBUG("token= " << token << "\n");
#endif
	ipJob.resize(vecSize);
	for(int i=0; i < vecSize; i++){
		token= strtok(NULL, ">\n");
#ifdef DEBUG
	REPORT_DEBUG("token= " << token << "\n");
#endif
		ASSERT(1 == sscanf(token, "%[^\n]", buffer) );
		ipJob[i]= buffer;
	}
	
	token= strtok(NULL, delimiter);
	ASSERT2(1 == sscanf(token, "inputURL=%[^\n]", buffer), "token = " << token );
	inputURL= buffer;
#ifdef DEBUG
	REPORT_DEBUG("token= " << token << "\n");
#endif
	
	token= strtok(NULL, ">\n");
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
	
	token= strtok(NULL, ">\n");
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

bool Job::operator==(Job const &other){
	bool ret= true;
	ret= ret && (id==other.id);
	ret= ret && (testId == other.testId);
	ret= ret && (localID == other.localID);
	ret= ret && (serviceId == other.serviceId);
	ret= ret && (args == other.args);
	ret= ret && (ipJob == other.ipJob);
	ret= ret && (inputURL == other.inputURL);
	ret= ret && (outputs == other.outputs);
	ret= ret && (timestamp == other.timestamp);
	ret= ret && (worstExecution == other.worstExecution);
	ret= ret && (dependecies == other.dependecies);
	ret= ret && (referenceFile == other.referenceFile);
	ret= ret && (useCPU == other.useCPU);
	ret= ret && (useGPU == other.useGPU);
	ret= ret && (gpuPref == other.gpuPref);
	return ret;
}

bool Job::TestSerialization(void){
	Job a;
	a.id = "testeId";
	a.testId= 1;
	a.localID= "testelLocalID";
	a.serviceId= "testelServiderId";
	a.args= "testeargs";
	a.ipJob.push_back("Teste1");
	a.ipJob.push_back("Teste2");
	a.inputURL= "uma.url";
	a.outputs.push_back("output1");
	a.outputs.push_back("output2");
	a.timestamp= 123123;
	a.worstExecution= 123.35678;
	a.dependecies.push_back("dep1");
	a.dependecies.push_back("dep2");
	a.referenceFile= "ref";
	a.useCPU= true;
	a.useGPU= false;
	a.gpuPref= 1.27;
	std::string serializated= a.Serialize();
	printf("\n------\n%s\n------\n", serializated.c_str());
	Job b(serializated);
	return a==b;
}



