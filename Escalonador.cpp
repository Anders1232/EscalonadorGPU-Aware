#include <queue>
#include "Escalonador.hpp"

using std::priority_queue

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
	vector<JobInfo*> jobsWithUnsuedCPU;
	vector<JobInfo*> jobsWithUnsuedGPU;
	priority_queue<JobInfo*> jobsWithNoDependencies(CompareJobsByDuration);
	
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
				uint64_t dependecyJobID= job.idOfJobsWhomIDepend[count];
				bloquedJobs[dependecyJob].emplace(bloquedJobs[dependecyJob].end(), job);
			}
		}
		if(!job.UseCPU())
		{
			jobsWithUnsuedCPU.push_back(&job);
		}
		if(!job.UseGPU())//otimização: usar else if no lugar de if
		{
			jobsWithUnsuedGPU.push_back(&job);
		}
	}
	
	priority_queue<JobInfo*> cpuJobsWoutDep(CompareJobsByDuration);
	priority_queue<JobInfo*> gpuJobsWoutDep(CompareJobsByDuration);
	
	limitCounter= jobsWithNoDependencies.size();
	for(int count =0; count < limitCounter; count++)
	{
		JobInfo& job= *(jobsWithNoDependencies[count]);
		if(job.UseCPU())
		{
			cpuJobsWoutDep.push_back(&job);
		}
		if(job.UseGPU())
		{
			gpuJobsWoutDep.push_back(&job);
		}
	}
	
	int counter=0;
	limitCounter= jobsWithUnsuedCPU.size();
	for(int  count=0; count < limitCounter)
	{
		
	}
}
void Scheduler::JobEnded(uint64_t jobID)
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
	//Escalonar unblockedJobs
}

