#include "Simulation.h"

Simulation::Simulation(QObject *parent) :
	QObject(parent),
	watchdog_(this),
	round_timer_(this) {

	population_.inflateRandom();
	watchdog_.setInterval(CHECK_TIME);
	round_timer_.setInterval(MAX_ROUND_TIME);
	round_timer_.setSingleShot(true);
	connect(&watchdog_, SIGNAL(timeout()), this, SLOT(checkActivity()));
	connect(&round_timer_, SIGNAL(timeout()), this, SLOT(endRound()));
	watchdog_.start();
	round_timer_.start();
}
void Simulation::clearVehicles() {
	for (auto& vehicle : vehicles_) {
		vehicle.destroy();
	}
	vehicles_.clear();
	fitnesses_.clear();
}
void Simulation::newGround() {
	if (ground_ != nullptr)
	{
		Physics::ObjectsFactory::getInstance().destroyBody(*ground_.get());
	}
	ground_.reset();
	ground_ = std::shared_ptr<Objects::Ground>(GroundGenerator(TRACK_SEGMENTS, TRACK_SEGMENT_WIDTH, TRACK_SEGMENTS_DELTA).genereteNew({ -CARS_START_X, -CARS_START_Y }));
}
void Simulation::newVehicles() {
	clearVehicles();

	for (const auto& genotype : population_.getGenotypes()) {
		vehicles_.push_back(genotype.generate());
		fitnesses_.emplace_back(0.0f);
	}
}
void Simulation::reset() {
	newGround();
	population_.reset();
	newVehicles();
	resetTimers();
}
void Simulation::stop() {
	watchdog_.stop();
	round_timer_.stop();
}
void Simulation::start() {
	watchdog_.start();
	round_timer_.start();
}
void Simulation::checkActivity() {
	bool active = false;
	for (std::size_t i = 0; i < vehicles_.size(); ++i) {
		float x_position = vehicles_[i].getPosition().x;
		if (x_position - 0.1f > fitnesses_[i]) {
			fitnesses_[i] = x_position;
			active = true;
		}
	}
	if (!active)
		endRound();
}
void Simulation::setPopulationSize(std::size_t new_size) {
	population_.setNextGenerationSize(new_size);
}
const std::vector<Objects::Vehicle> Simulation::getVehicles() const {
	return this->vehicles_;
}
const std::weak_ptr<Objects::Ground> Simulation::getGround() const {
	return this->ground_;
}
const Objects::Vehicle& Simulation::getBestVehicle() const {
	const Objects::Vehicle* best_vehicle = nullptr;

	for (const auto& vehicle : vehicles_) {
		if (best_vehicle == nullptr)
			best_vehicle = &vehicle;
		else if (best_vehicle->getPosition().x < vehicle.getPosition().x)
			best_vehicle = &vehicle;
	}

	return *best_vehicle;
}
std::size_t Simulation::getPopulationSize() const {
	return population_.getNextGenerationSize();
}
void Simulation::setMutationRate(float mutation_rate) {
	population_.setMutationRate(mutation_rate);
}
float Simulation::getMutationRate() const {
	return population_.getMutationRate();
}
void Simulation::endRound() {
	emit roundEnd(fitnesses_);
	auto& genotypes = population_.getGenotypes();
	for (std::size_t i = 0; i < fitnesses_.size(); ++i) {
		genotypes[i].fitness = std::fmaxf(0.0f, fitnesses_[i]);
	}
	population_.nextPopulation();
	newVehicles();

	round_timer_.start(MAX_ROUND_TIME);
}
std::size_t Simulation::getEliteSpecimen() const {
	return population_.getEliteSpecimen();
}
void Simulation::setEliteSpecimen(std::size_t elite_specimen) {
	population_.setEliteSpecimen(elite_specimen);
}
void Simulation::loadFromFile(std::string filename) {
	population_.loadFromFile(filename);

	newVehicles();
	resetTimers();
}
void Simulation::saveToFile(std::string filename) const {
	population_.saveToFile(filename);
}
void Simulation::resetTimers() {
	watchdog_.start(CHECK_TIME);
	round_timer_.start(MAX_ROUND_TIME);
}