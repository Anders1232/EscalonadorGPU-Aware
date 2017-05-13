#include <queue>
#include <array>
#include <string>
#include <algorithm>
#include "Escalonador.hpp"

using std::priority_queue;
using std::array;
using std::string;

#define JOB_TO_BE_DETERMINED 0
#define MACHINE_WITHOUT_GPU -1
/*
Scheduler::Scheduler(Communicator* comunicator): comunicator(comunicator)
{
}
*/

class CompareJobsByDuration
{
	public:
		inline bool operator()(JobInfo &a, JobInfo &b)
		{
			return a.execTime < b.execTime;
		}
		inline bool operator()(JobInfo *a, JobInfo *b)
		{
			return a->execTime < b->execTime;
		}
};

void Scheduler::AddJobs(vector<JobInfo> *newJobs)
{
	vector<shared_ptr< JobInfo> > jobsWithNoDependencies;
	
	int limitCounter= newJobs->size();
	for(int count =0; count < limitCounter; count++)
	{
		JobInfo& job= (*newJobs)[count];
		if(job.idOfJobsWhomIDepend.empty())
		{
			jobsWithNoDependencies.emplace_back(&job);
		}
		else
		{
			shared_ptr<JobInfo> jobWithDependencies(&job);
			int numJobsWithDep= job.idOfJobsWhomIDepend.size();
			for(int count=0; count < numJobsWithDep; count++)
			{
				int64_t dependecyJobID= job.idOfJobsWhomIDepend[count];
				bloquedJobs[dependecyJobID].emplace_back(jobWithDependencies);
			}
		}
	}
	
	ScheduleJobs(jobsWithNoDependencies);
}

void Scheduler::JobEnded(int64_t jobID)
{
	if(bloquedJobs.end() == bloquedJobs.find (jobID))
	{
		return;
	}
	vector<shared_ptr<JobInfo> > unblockedJobs= bloquedJobs[jobID];
//	int limitCounter= unblockedJobs.size();
//	for(int count =0; count < limitCounter; count++)
	for(vector<shared_ptr<JobInfo>>::iterator it = unblockedJobs.begin(); it != unblockedJobs.end(); )
	{
		if( (*it).unique())
		{
			unblockedJobs.emplace_back(it);
			it= unblockedJobs.erase(it);
		}
		else
		{
			it++;
		}
	}
	ScheduleJobs(unblockedJobs);
}

void Scheduler::ScheduleJobs(vector<shared_ptr< JobInfo > > const &jobsToSchedule)
{
	int numberOfMachines= 0;
	vector<JobInfo*> cpuJobsWoutDep;
	vector<JobInfo*> gpuJobsWoutDep;
// isso pode ser rodado em paralelo com...
	for(size_t count =0 ; count < jobsToSchedule.size(); count++)
	{
		JobInfo &job= (*(jobsToSchedule[count]) );
		for(size_t count2= 0; count2< job.MachinesToInstantiate.GetListSize(); count++)
		{
			numberOfMachines+= job.MachinesToInstantiate[count2].numberOfMachines;
		}
		if(job.UseCPU())
		{
			cpuJobsWoutDep.push_back(&job);
		}
		if(job.UseGPU())
		{
			gpuJobsWoutDep.push_back(&job);
		}
	}
//	array<std::string, numberOfMachines> machines;
//	array<int64_t, numberOfMachines> CPUJobID;
//	array<int64_t, numberOfMachines> GPUJobID;
	std::string *machines;
	machines= new std::string[numberOfMachines];
//	std::string machines[numberOfMachines];
	int64_t CPUJobID[numberOfMachines];
	int64_t GPUJobID[numberOfMachines];
// ...isso
	{
		int machineCounter= 0;
		for(size_t count =0; count < jobsToSchedule.size(); count++)
		{
			JobInfo &job= *jobsToSchedule[count];
			for(size_t count=0; count < job.MachinesToInstantiate.GetListSize(); count++)
			{
				machines[machineCounter]= string(job.MachinesToInstantiate[count].machineType.machineName);
				CPUJobID[machineCounter]= (job.UseCPU() )? job.id : JOB_TO_BE_DETERMINED;
				CPUJobID[machineCounter]= (job.MachinesToInstantiate[count].machineType.HaveGPU())?
											(job.UseGPU() )?
													job.id
													: JOB_TO_BE_DETERMINED
											: MACHINE_WITHOUT_GPU;
				machineCounter++;
			}
		}
	}
	//ja temos a tabela de máquina x CPU/GPU preenchida com as informações fornecidas ao escalonador,
	//agora vamos fazer o escalonador escolher jobs pára usarem unidades de processamento não escalonadas.
	CompareJobsByDuration comparer;
	std::sort(cpuJobsWoutDep.begin(), cpuJobsWoutDep.end(), comparer);
	std::sort(gpuJobsWoutDep.begin(), gpuJobsWoutDep.end(), comparer);
	int lastHelpedJob=0;
	for(int count= 0; count < numberOfMachines; count++)
	{
		if(JOB_TO_BE_DETERMINED == CPUJobID[count])
		{
			CPUJobID[count] = cpuJobsWoutDep[lastHelpedJob%cpuJobsWoutDep.size()]->id;
			lastHelpedJob++;
		}
	}
	lastHelpedJob=0;
	for(int count= 0; count < numberOfMachines; count++)
	{
		if(JOB_TO_BE_DETERMINED == GPUJobID[count])
		{
			GPUJobID[count] = gpuJobsWoutDep[lastHelpedJob%gpuJobsWoutDep.size()]->id;
			lastHelpedJob++;
		}
	}
	//aqui usar o comunicador para enviar esse reultado para o programa JAVA

	delete [] machines;
}

