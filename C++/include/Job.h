#ifndef JOB_H
#define JOB_H

#include <stdio.h>
#include<string>
#include <stdint.h>
#include <vector>
#include <Serializable.h>

class Job : public Serializable<Job>
{
	public:
		static char* Serialize(Job& instance);
		static Job Deserialize(char* data);
		Job(void);
//	private:
		std::string id;
		int64_t testId;
		std::string localID, serviceId, args;
		std::vector<std::string> ipJob;//ver o que Transient significa
		std::vector<FILE*> inputFiles;
		std::string inputURL;
		std::vector<std::string> outputs;
		int64_t timestamp;
		double worstExecution;
		std::vector<string> dependecies;
		std::string referenceFile;
		//adição
		bool useGPU, useCPU;
}

#endif // JOB_H
