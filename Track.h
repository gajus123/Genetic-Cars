#ifndef TRACK_H
#define TRACK_H

#include <vector>

class Track {
public:
	std::vector<std::pair<float, float> > getTrackPoints() const;
};

#endif