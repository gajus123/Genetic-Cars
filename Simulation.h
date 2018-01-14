#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <QObject>
#include <memory>
#include <vector>
#include "include\Vehicle.h"
#include "include\Ground.h"
#include "include\GroundGenerator.h"
#include "include\ObjectsFactory.h"
#include <cstdio>

class Simulation : public QObject {
	Q_OBJECT
public:
	Simulation(QObject *parent = Q_NULLPTR);
	void nextGeneration();

	const Objects::Vehicle& getBestVehicle() const;
	const std::vector<Objects::Vehicle> getVehicles() const;
	const std::weak_ptr<Objects::Ground> getGround() const;
	void newGround();
	void newVehicles();
public slots:
	void reset();
private:
	void clearVehicles();

	std::vector<Objects::Vehicle> vehicles_;
	std::shared_ptr<Objects::Ground> ground_;
	unsigned int population_size_;
};

#endif