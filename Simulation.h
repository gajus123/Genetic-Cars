/*!
* @authors Jakub Gajownik, Rafa³ Galczak
* @date 15.01.18
*
* \brief Simulation aggregate physics objects like Ground and Vehicles.
*        As well as being in charge of interacting with other systems using signals (observers).
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <memory>
#include <vector>
#include "include\Vehicle.h"
#include "include\Ground.h"
#include "include\GroundGenerator.h"
#include "include\ObjectsFactory.h"
#include <cstdio>
#include <cmath>
#include <QTimer>

class Simulation : public QObject {
	Q_OBJECT

	const std::size_t MAXIMUM_CARS = 30;
	const std::size_t TRACK_SEGMENTS = 1000;
	const float TRACK_SEGMENT_WIDTH = 1.2f;
	const float TRACK_SEGMENTS_DELTA = 1.0f;
	const std::size_t CARS_NUMBER_ON_START = 10;
	const float CARS_START_X = 1.0f;
	const float CARS_START_Y = -5.4f;
public:
	Simulation(QObject *parent = Q_NULLPTR);

	void stop();
	void start();
	void newGround();
	void newVehicles();
	void setPopulationSize(std::size_t newSize);

	std::size_t getPopulationSize() const;
	const Objects::Vehicle& getBestVehicle() const;
	const std::vector<Objects::Vehicle> getVehicles() const;
	const std::weak_ptr<Objects::Ground> getGround() const;
public slots:
	void reset();
	void checkActivity();
signals:
	void roundEnd(std::vector<float> distances);
private:
	void clearVehicles();

	QTimer watchdog_;

	unsigned int population_size_;
	std::vector<float> fitnesses_;
	std::vector<Objects::Vehicle> vehicles_;
	std::shared_ptr<Objects::Ground> ground_;
};

#endif