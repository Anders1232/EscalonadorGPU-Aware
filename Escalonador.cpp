#include <queue>
#include <array>
#include <string>
#include "Escalonador.hpp"

using std::priority_queue;
using std::array;
using std::string;

#define JOB_TO_BE_DETERMINED 0
#define MACHINE_WITHOUT_GPU -1

Scheduler::Scheduler(Communicator* comunicator): comunicator(comunicator)
{
}

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
}

void Scheduler::AddJobs(vector<JobInfo> *newJobs)
{
	vector<shared_ptr< JobInfo> > jobsWithNoDependencies();
	
	int limitCounter= newJobs->size();
	for(int count =0; count < limitCounter; count++)
	{
		JobInfo& job= (*newJobs)[count];
		if(job.idOfJobsWhomIDepend.empty())
		{
			jobsWithNoDependencies.push_back(&job);
		}
		else
		{
//			shared_ptr<JobInfo> jobWithDependencies(job);
			int numJobsWithDep= job.idOfJobsWhomIDepend.size();
			for(int count=0; count < numJobsWithDep; count++)
			{
				int64_t dependecyJobID= job.idOfJobsWhomIDepend[count];
				bloquedJobs[dependecyJob].emplace_back(&job);
			}
		}
	}
	
	ScheduleJobs(jobsWithNoDependencies);
}

void Scheduler::JobEnded(int64_t jobID)
{
	if(bloquedJobs.end() == bloquedJobs.find (jobID))
	vector<shared_ptr<JobInfo> > unblockedJobs;
//	int limitCounter= bloquedJobs[jobID].size();
//	for(int count =0; count < limitCounter; count++)
	for(vector<shared_ptr<jobInfo>>::iterator it= bloquedJobs.begin; it != bloquedJobs.end(); )
	{
		if((bloquedJobs[jobID][counter].unique())
		{
			unblockedJobs.emplace(unblockedJobs.end(), bloquedJobs[jobID][counter]);
			it= unblockedJobs.erase(it);
		}
		else
		{
			it++;
		}
	}
	ScheduleJobs(unblockedJobs);
}

void Scheduler::ScheduleJobs(vector<shared_ptr<JobInfo> > const &jobsToSchedule)
{
	int numberOfMachines= 0;
	priority_queue<JobInfo*> cpuJobsWoutDep(CompareJobsByDuration);
	priority_queue<JobInfo*> gpuJobsWoutDep(CompareJobsByDuration);
// isso pode ser rodado em paralelo com...
	for(int count =0 ; count < jobsToSchedule.size(); count++)
	{
		JobInfo &job= jobsToSchedule[count];
		numberOfMachines+= job.MachinesToInstantiate.numberOfMachines;
		if(job.UseCPU())
		{
			cpuJobsWoutDep.push(&job);
		}
		if(job.UseGPU())
		{
			gpuJobsWoutDep.push(&job);
		}
	}
	array<std::string, numberOfMachines> machines;
	array<int64_t, numberOfMachines> CPUJobID;
	array<int64_t, numberOfMachines> GPUJobID;
// ...isso
	for(int count =0, int machineCounter=0 ; count < jobsToSchedule.size(); count++)
	{
		JobInfo &job= jobsToSchedule[count];
		for(int count=0; count < job.MachinesToInstantiate.numberOfMachines; count++)
		{
			machines[machineCounter]= string(job.MachinesToInstantiate[count].machineName);
			CPUJobID[machineCounter]= (job.UseCPU() )? job.id : JOB_TO_BE_DETERMINED;
			CPUJobID[machineCounter]= (job.MachinesToInstantiate[count].machineType.HaveGPU())?
										(job.UseGPU() )?
												job.id
												: JOB_TO_BE_DETERMINED
										: MACHINE_WITHOUT_GPU;
			machineCounter++;
		}
	}
	//ja temos a tabela de máquina x CPU/GPU preenchida com as informações fornecidas ao escalonador,
	//agora vamos fazer o escalonador escolher jobs pára usarem unidades de processamento não escalonadas.
	int lastHelpedJob=0;
	for(int count= 0; count < machines.size(); count++)
	{
		if(JOB_TO_BE_DETERMINED == CPUJobID[count])
		{
			CPUJobID[count] = cpuJobsWoutDep[lastHelpedJob++];
		}
	}
	lastHelpedJob=0;
	for(int count= 0; count < machines.size(); count++)
	{
		if(JOB_TO_BE_DETERMINED == GPUJobID[count])
		{
			GPUJobID[count] = gpuJobsWoutDep[lastHelpedJob++];
		}
	}
	//aqui usar o comunicador para enviar esse reultado para o programa JAVA
}

