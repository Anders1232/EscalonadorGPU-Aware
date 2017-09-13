#ifndef SIMPLERATINGSCHED_H
#define SIMPLERATINGSCHED_H

#include "Escalonador.hpp"
#include "SimpleRatingMethod.h"

class SimpleRatingSched: public Escalonador{
	public:
		std::unique_ptr<std::unordered_map<Job, PluginInfo>> Schedule(std::vector<Job> jobs);
		std::string GetPolicyName(void);
	private:
		SimpleRatingMethod ratingMethod;
};

#endif // SIMPLERATINGSCHED_H
