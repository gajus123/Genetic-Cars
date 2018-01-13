#include "Track.h"

std::vector<std::pair<float, float> > Track::getTrackPoints() const
{
	static std::vector<std::pair<float, float> > track = {
		std::make_pair<float, float>(4.0f, 200.0f),
		std::make_pair<float, float>(104.0f, 180.0f),
		std::make_pair<float, float>(204.0f, 180.0f),
		std::make_pair<float, float>(304.0f, 190.0f),
		std::make_pair<float, float>(404.0f, 170.0f),
		std::make_pair<float, float>(504.0f, 180.0f)
	};
	return track;
}