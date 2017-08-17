#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>
#include <string>

#include "PluginInfo.h"
#include "Job.h"
#include "RatingMethod.h"

using std::vector;
using std::unordered_map;
using std::shared_ptr;
using std::unique_ptr;

class Escalonador
{
	public:
		RatingMethod *ratingMethod;
		unique_ptr<unordered_map<Job, PluginInfo>> Schedule(vector<Job> jobs);
		vector<PluginTask> Relocate(vector<std::pair<Job, PluginTask> > taskPairs);
		void CancelJobEvent(PluginTask task);
		std::string GetPolicyName(void);
}

#endif
