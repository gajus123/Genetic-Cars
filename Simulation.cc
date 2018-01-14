#include "Simulation.h"

Simulation::Simulation(QObject *parent) :
	QObject(parent),
	population_size_(10) {

}
void Simulation::clearVehicles() {
	for (auto& vehicle : vehicles_) {
		vehicle.destroy();
	}
	vehicles_.clear();
}
void Simulation::newGround() {
	if (ground_ != nullptr)
	{
		Physics::ObjectsFactory::getInstance().destroyBody(*ground_.get());
	}
	ground_.reset();
	ground_ = std::shared_ptr<Objects::Ground>(GroundGenerator(1000, 1.2, 1.0f).genereteNew({ -1.0f, 5.0f }));
}
void Simulation::newVehicles() {
	clearVehicles();
	
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> uni(0.3, 1.0);


	for (std::size_t i = 0; i < population_size_; ++i) {
		/*vehicles_.push_back(Objects::Vehicle(Objects::Vector2(0, 0.4), { 0.2f, 0.2f, 0.5f, 0.28f, 0.2f, 0.28f, 0.5f, 0.2f }, 0.35f, 0.35f));
		vehicles_.push_back(Objects::Vehicle(Objects::Vector2(0, 0.4), { 0.2f, 0.2f, 0.5f, 0.28f, 0.2f, 0.28f, 0.5f, 0.2f }, 0.4f, 0.4f));*/
		std::vector<float> points;
		for (std::size_t i = 0; i < 8; ++i) {
			points.push_back(uni(rng));
		}
		vehicles_.push_back(Objects::Vehicle(Objects::Vector2(0, 0.4), points, uni(rng), uni(rng)));
	}
}
void Simulation::reset() {
	newGround();
	newVehicles();
}
const std::vector<Objects::Vehicle> Simulation::getVehicles() const {
	return this->vehicles_;
}
const std::weak_ptr<Objects::Ground> Simulation::getGround() const {
	return this->ground_;
}
const Objects::Vehicle& Simulation::getBestVehicle() const {
	const Objects::Vehicle* bestVehicle = nullptr;

	for (const auto& vehicle : vehicles_) {
		if (bestVehicle == nullptr)
			bestVehicle = &vehicle;
		else if (bestVehicle->getPosition().x < vehicle.getPosition().x)
			bestVehicle = &vehicle;
	}

	return *bestVehicle;
}