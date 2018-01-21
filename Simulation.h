//
// \author Jakub Gajownik
// \date 15.01.18
//

#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <memory>
#include <vector>
#include <cmath>

#include "include/Vehicle.h"
#include "include/Ground.h"
#include "include/GroundGenerator.h"
#include "include/ObjectsFactory.h"

/*!
	\class Simulation
	\brief Simulation aggregate physics objects like Ground and Vehicles.
	Checks vehicles activity. If none of the vehicles are moving forward it inform about it other modules.
*/
class Simulation : public QObject {
	Q_OBJECT

	const std::size_t TRACK_SEGMENTS = 1000;
	const float TRACK_SEGMENT_WIDTH = 1.2f;
	const float TRACK_SEGMENTS_DELTA = 1.0f;
	const float CARS_START_X = 6.0f;
	const float CARS_START_Y = -5.4f;
	const std::size_t CHECK_TIME = 3000;
	const std::size_t MAX_ROUND_TIME = 60000;
public:
	Simulation(QObject *parent = Q_NULLPTR);

	void stop(); //!  If simulation is running, it stops checking vehicles acitivity
	void start(); //!  If simulation is not running, it resumes checking vehicles acitivity
	void newGround();
	void resetTimers(); //!  Resets activity checking

	void setTimeSpeed(float time_speed); //!  Sets time speed multiplier - 1.0 is normal speed

	const Objects::Vehicle& getBestVehicle() const; //!  Returns vehicle with the biggest fitness value
	const std::vector<Objects::Vehicle> getVehicles() const;
	const std::weak_ptr<Objects::Ground> getGround() const;
public slots:
	void reset(); //!  Resets simulation and generate new ground
	void newRound(std::vector<Objects::Vehicle> vehicles); //!  Starts new simulation round with passed vehicles
private slots:
	void endRound();
	void checkActivity(); //!  Checks wheater vehicles are still moving, if not it sends roundEnd signal
signals:
	void roundEnd(std::vector<float> distances);
private:
	void clearVehicles();
	void saveRemainingTime();

	QTimer watchdog_;
	QTimer round_timer_;

	bool is_running_;
	int round_time_left_;
	int watchdog_time_left_;
	float time_speed_;
	std::vector<float> fitnesses_;
	std::vector<Objects::Vehicle> vehicles_;
	std::shared_ptr<Objects::Ground> ground_;
};

#endif