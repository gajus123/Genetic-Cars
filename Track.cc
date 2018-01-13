#include "Track.h"

std::vector<std::pair<float, float> > Track::getTrackPoints() const
{
	static std::vector<std::pair<float, float> > track = {
		std::make_pair<float, float>(4.0f, 400.0f),
		std::make_pair<float, float>(104.0f, 380.0f),
		std::make_pair<float, float>(204.0f, 380.0f),
		std::make_pair<float, float>(304.0f, 390.0f),
		std::make_pair<float, float>(404.0f, 370.0f),
		std::make_pair<float, float>(504.0f, 380.0f),
		std::make_pair<float, float>(604.0f, 420.0f),
		std::make_pair<float, float>(704.0f, 400.0f),
		std::make_pair<float, float>(804.0f, 380.0f),
		std::make_pair<float, float>(904.0f, 430.0f),
		std::make_pair<float, float>(1004.0f, 410.0f),
		std::make_pair<float, float>(1104.0f, 400.0f)
	};
	return track;
}