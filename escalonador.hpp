#include <cstdint>
#include <vector>

using std::vector;

struct TipoJob
{
	uint64_t id;
	(double) (*comoEscalaNaCPU)(uint64_t tamanhoDaEntrada);
	(double) (*comoEscalaNaGPU)(uint64_t tamanhoDaEntrada);
};

struct Job
{
	uint64_t id;
	uint64_t dependencia;
	uint64_t idTipoJob;
	uint64_t tamanhoDaEntrada;
};

/*
	Ver como o escalonador vai informar a alguém que algo deve ser escalonado.
	Estou pensando em usar sockets para isso.
*/
class Escalonador
{
	public:
		void AdicionarJob(Job);
		void JobTerminado(uint64_t jobID);
	private:
		vector<TipoJob> tipoJob;
};
