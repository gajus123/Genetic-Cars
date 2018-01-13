#ifndef CAR_H
#define TRACK_H

#include <vector>

class Car {
public:
	std::vector<std::pair<float, float> > getShapePoints() const;
	std::pair<float, float> getPosition() const;
	std::vector<std::pair<std::pair<float, float>, float> > getWheels() const;
};

#endif