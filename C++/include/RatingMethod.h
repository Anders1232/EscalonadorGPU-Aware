#ifndef RATINGMETHOD_H
#define RATINGMETHOD_H

#include "PluginInfo.h"

class RatingMethod
{
	public:
		virtual double Rate(PluginInfo &spec)=0;
}

#endif // RATINGMETHOD_H
