#include <Statistics.h>

void Statistics::calculateStatistics(std::vector<float> distances) {
	float best = *std::max_element(distances.begin(), distances.end());
	float worst = *std::min_element(distances.begin(), distances.end());
	float average = 0.0f;
	float median = 0.0f;

	for (const auto& distance : distances) {
		average += distance;
	}
	average /= distances.size();

	if (distances.size() % 2 == 1)
		median = distances[distances.size() / 2];
	else
		median = (distances[distances.size() / 2] + distances[distances.size() / 2 - 1]) / 2.0f;

	emit newValues(best, worst, average, median);
}