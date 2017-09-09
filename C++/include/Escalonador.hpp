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

class Escalonador
{
	public:
		virtual std::unique_ptr<std::unordered_map<Job, PluginInfo>> Schedule(std::vector<Job> jobs)=0;
//		vector<PluginTask> Relocate(vector<std::pair<Job, PluginTask> > taskPairs);
//		void CancelJobEvent(PluginTask task);
		virtual std::string GetPolicyName(void) =0;
		void UpdateCloudMap(std::unique_ptr<std::unordered_map<std::string, PluginInfo> > newMap);
	private:
		std::unique_ptr<std::unordered_map<std::string, PluginInfo> > cloudMap;
};

#endif
