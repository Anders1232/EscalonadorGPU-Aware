#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include <stdint.h>
//#include <stdbool.h>
#include "Vector.h"

#define JOB_NOT_EXECUTABLE_ON_CPU (0x1)//informa que o Job não pode ser executado em CPU
#define JOB_NOT_EXECUTABLE_ON_GPU (0x3)//informa que o Job não pode ser executado em GPU

struct jobInfo
{
	uint64_t id;
	uint64_t idOfJobWhomIDepend;//verificar se pode haver dependência de mais de um job
	unsigned int flags;
	unsigned int requestedNumberOfNodes;
	double **execTime;//execTime é uma matriz triangular superior esquerda 4x4. No qual a dimensâo de maior grau refete-se ao número de GPUs(0, N/4, N/2, N). A dimensão de maior grau refere-se ao número de CPUs(0, N/4, N/2, N).
};
typedef struct jobInfo JobInfo;

//Esses vector estão meio que pseudocódigo. Vou ver se faço uso do Vector q fiz um tempo atrás um crio uma estrutura de hash no C.
struct scheduler
{
//	Vector<Vector<JobInfo>> jobPerReqNodes;
	Vector *jobPerReqNodes;
//	Vector<JobInfo> blockedJobs;
	Vector *blockedJobs;
	Communicator comunication;
};
typedef struct scheduler Scheduler;
//Estou pensando se é necessário ter a função escalonar, ou se o escalonador é completamente orientado e eventos, ou seja, toda vez que ele receber um conjunto de Jobs para ser executado ele automaticamente já envia mensagens ordenando que os jobs que podem ser escalonados os sejam
void AddJobs(Scheduler *, JobInfo *jobs, int jobsSize);
void JobEnded(uint64_t jobID);

#endif
