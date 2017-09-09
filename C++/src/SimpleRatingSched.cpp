#include "SimpleRatingSched.h"


bool JobComparer(Job const &a, Job const &b){
	return a.worstExecution < b.worstExecution;
}

bool PluginInfoComparer(PluginInfo const &a, PluginInfo const &b){
	return a.ranking < b.ranking;
}

std::unique_ptr<std::unordered_map<Job, PluginInfo>> SimpleRatingSched::Schedule(std::vector<Job> jobs){
	std::vector<Job> sortedJobs(jobs.begin(), jobs.end());
	std::sort(sortedJobs.begin(), sortedJobs.end(), JobComparer());
	std::vector<PluginInfo> machines((*cloudMap).begin(), (*cloudMap).end());
	std::sort(machines.begin(), machines.end(), PluginInfoComparer());
	
}
std::string SimpleRatingSched::GetPolicyName(void);

