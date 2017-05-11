#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <memory>

using std::vector;
using std::unordered_map;
using std::shared_ptr;
using std::unique_ptr;

#define JOB_NOT_EXECUTABLE_ON_CPU (0x1)//informa que o Job não pode ser executado em CPU
#define JOB_NOT_EXECUTABLE_ON_GPU (0x2)//informa que o Job não pode ser executado em GPU
#define JOB_WILL_USE_CPU (0x4)//informa que o Job não pode ser executado em CPU
#define JOB_WILL_USE_GPU (0x5)//informa que o Job não pode ser executado em GPU

//\todo criar flag DO_NOT_SCHEDULE para jobs que não podem rodar em mais de um job

struct MachineType
{
	char * machineName;
	int64_t CPUPerfPoints;
	int64_t GPUPerfPoint;//zero ou negativo significa não roda em GPU
	inline bool HaveGPU(void)
	{
		return (GPUPerfPoint>0);
	}
};

struct MachinesList
{
	public:
		size_t GetListSize(void) const;
		struct Element;
		Element operator[](int index);
	private:
		vector<MachineType> machinesToInstantiate;
		vector<int> numMachinesToInstantiatePerMachineType;
		vector<int> flags
};

struct MachinesList::Element
{
	public:
		MachinesList::Element(int, bool willUseCPu, bool willUseGPU, MachineType);
		int numberOfMachines;
		MachineType machineType;
	private:
//		int flags;
}

struct JobInfo
{
	int64_t id;
	vector<int64_t> idOfJobsWhomIDepend;
	unsigned int flags;
	MachineList MachinesToInstantiate;
	double execTime;//execTime é uma matriz triangular superior esquerda 4x4. No qual a dimensâo de maior grau refete-se ao número de GPUs(0, N/4, N/2, N). A dimensão de maior grau refere-se ao número de CPUs(0, N/4, N/2, N).
	inline bool UseCPU(void) const
	{
		return (false==(JOB_NOT_EXECUTABLE_ON_CPU & flags));
	}
	inline bool UseGPU(void) const
	{
		return (false==(JOB_NOT_EXECUTABLE_ON_GPU & flags));
	}
};

//Esses vector estão meio que pseudocódigo. Vou ver se faço uso do Vector q fiz um tempo atrás um crio uma estrutura de hash no C.
class Scheduler
{
	public:
		Scheduler(Communicator* comunicator);
		void AddJobs(vector<JobInfo> *newJobs);
		void JobEnded(int64_t jobID);
	private:
		void ScheduleJobs(vector<shared_ptr<JobInfo> > &jobsToSchedule);
		unordered_map<int64_t/*id*/, vector<shared_ptr<JobInfo> > > bloquedJobs;
		unique_ptr<Communicator> comunicator;
};

#endif
