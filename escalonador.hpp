#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>

using std::vector;
using std::unordered_map;
using std::string;
//using std::

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
		void JobTerminado(uint64_t jobID, double duracao);
		void AdicionarJob(uint64_t id, TipoJob dados);
	private:
		class TipoJob;
		unordered_map<uint64_t, TipoJob> tabelaTipoJob;// a chave desse hash será o id do tipo de Job
		vector<Job> listaJobsCPU;
		vector<Job> listaJobsGPU;
		vector<Job> jobsBloqueadosCPU;
		vector<Job> jobsBloqueadosGPU;
};

class Escalonador::TipoJob
{
	public:
		uint64_t ObterPontuacao(uint64_t tamanhoDaEntrada) const;
		uint64_t EnviarFeedback(uint64_t tamanhoDaEntrada, double duracao);
		string ObterNome(void) const;
		Escalonador::TipoJob
		(
			string nome,
			uint64_t pontuacaoEmCPU,
			uint64_t pontuacaoEmGPU,
			(uint64_t) (*comoEscalaNaCPU)(uint64_t tamanhoDaEntrada, uint64_t pontuacaoEmCPU),
			(uint64_t) (*comoEscalaNaGPU)(uint64_t tamanhoDaEntrada, uint64_t pontuacaoEmGPU)//será que é necessário métodos para informar como o feddback deve alterar a pontuação??
		);
	private:
		string nome;
		uint64_t pontuacaoEmCPU;
		uint64_t pontuacaoEmGPU;
		(uint64_t) (*comoEscalaNaCPU)(uint64_t tamanhoDaEntrada, uint64_t pontuacaoEmCPU);
		(uint64_t) (*comoEscalaNaGPU)(uint64_t tamanhoDaEntrada, uint64_t pontuacaoEmGPU);
};

