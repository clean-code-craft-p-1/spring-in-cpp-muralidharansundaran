#include <vector>
#include <math.h>
#include <cmath>
#include <numeric>

//#define NAN (std::numeric_limits<double>::quiet_NaN())

namespace Statistics {
	// define the Stats structure here. See the tests to infer its properties

	struct Stats
	{
		double average;
		double max;
		double min;
	};

	Stats ComputeStatistics(const std::vector<double>&);

	template <typename T>
	T FindAverage(const std::vector<T>& vec) {
		T sum = std::accumulate(vec.begin(), vec.end(), 0.0);
		if (sum == 0)
			return NAN;
		else
			return sum / static_cast<double>(vec.size());
	}

	template <typename T>
	T FindMax(const std::vector<T>& vec) {
		return *max_element(vec.begin(), vec.end());
	}

	template <typename T>
	T FindMin(const std::vector<T>& vec) {
		return *min_element(vec.begin(), vec.end());
	}
}

class IAlerter
{
public:
	virtual void sendAlert() = 0;
};

class EmailAlert : public IAlerter
{
public:
	virtual void sendAlert() override;
	bool emailSent = false;
};


class LEDAlert :public IAlerter
{
public:
	virtual void sendAlert() override;
	bool ledGlows = false;
};



class StatsAlerter
{
public:
	StatsAlerter(float maxThreshold, std::vector<IAlerter*> alerters);
	void checkAndAlert(const std::vector<double>& val);
private:
	float maxThreshold;
	std::vector<IAlerter*> alerters;
};
