#include "Car.h"

std::vector<std::pair<float, float> > Car::getShapePoints() const {
	static std::vector<std::pair<float, float> > shape = {
		std::make_pair<float, float>(-100.0f, 0.0f),
		std::make_pair<float, float>(0.0f, 50.0f),
		std::make_pair<float, float>(100.0f, 0.0f),
		std::make_pair<float, float>(0.0f, -50.0f)
	};
	return shape;
}
std::pair<float, float> Car::getPosition() const {
	return std::make_pair<float, float>(200.0f, 100.0f);
}
std::vector<std::pair<std::pair<float, float>, float> > Car::getWheels() const {
	static std::vector<std::pair<std::pair<float, float>, float> > wheels = {
		std::make_pair<std::pair<float, float>, float>(std::make_pair<float, float>(-100.0f, 0.0f), 50.0f),
		std::make_pair<std::pair<float, float>, float>(std::make_pair<float, float>(100.0f, 0.0f), 50.0f)
	};
	return wheels;
}