#ifndef PLUGININFO_H
#define PLUGININFO_H

#include <string>
#include <vector>
#include <stdint.h>
#include "Host.h"

class PluginInfo
{
	public:
		std::string id;
		std::string instanceName;
		int privateCloud;
		Host host;
		int64_t upTime;
		double latency;
		double costPerGiga;
		int64_t timestamp;
		int numCores, numNodes, numOccupied;
		double ranking;
		float fsSize;
		double memoryTotal, memoryFree, currentFrequencyCore;
//		std::vector<PluginService> services;
		double costPerHour, bandwith;
		std::string ip, provider;
		//adição
		double gpuMemoryTotal,
			gpuMemoryMaxFrequency,
			gpuMemoryBus,
			gpuMemoryBandwith,
			gpuFloatingPointPerf;
		double gpuMaxFrequency;
};

#endif // PLUGININFO_H
