//#include "pch.h"
#include "stats.h"
#include <limits.h>
#include <algorithm>

Statistics::Stats Statistics::ComputeStatistics(const std::vector<double>& vec)
{
	//Implement statistics here
	Stats value;

	if (vec.empty())
	{
		value.average = NAN;
		value.max = NAN;
		value.min = NAN;
	}
	else
	{
		value.average = FindAverage(vec);
		value.max = FindMax(vec);
		value.min = FindMin(vec);
	}

	return value;
}


void EmailAlert::sendAlert()
{
	emailSent = true;
}

void LEDAlert::sendAlert()
{
	ledGlows = true;
}

StatsAlerter::StatsAlerter(float maxThreshold, std::vector<IAlerter*> alerters)
{
	this->maxThreshold = maxThreshold;

	for (unsigned int i = 0; i < alerters.size(); i++)
	{
		this->alerters.push_back(alerters[i]);
	}

}
void StatsAlerter::checkAndAlert(const std::vector<double>& val)
{
	auto computeMax = Statistics::ComputeStatistics(val);
	if (computeMax.max > maxThreshold)
	{
		for (unsigned int i = 0; i < alerters.size(); i++)
		{
			//send sendAlert for all the alerters classes
			alerters[i]->sendAlert();
		}
	}
}