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

#include <Box2D/Box2D.h>

#include <World.h>
#include <Watchdog.h>
#include <Vehicle.h>
#include <Ground.h>
#include <GroundGenerator.h>
#include <ObjectsFactory.h>

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

	void newGround();
	void resetTimers(); //!  Resets activity checking

	const Objects::Vehicle& getBestVehicle() const; //!  Returns vehicle with the biggest fitness value
	const std::vector<Objects::Vehicle> getVehicles() const;
	const std::weak_ptr<Objects::Ground> getGround() const;
	World& getWorld();
public slots:
	void step(unsigned int time);
	void reset(); //!  Resets simulation and generate new ground
	void newRound(std::vector<Objects::Vehicle> vehicles); //!  Starts new simulation round with passed vehicles
private slots:
	void endRound();
	void checkActivity(); //!  Checks wheater vehicles are still moving, if not it sends roundEnd signal
signals:
	void roundEnd(std::vector<float> distances);
private:
	void clearVehicles();

	World world_;
	
	Watchdog activity_timer_;
	Watchdog round_timer_;

	std::vector<float> fitnesses_;
	std::vector<Objects::Vehicle> vehicles_;
	std::shared_ptr<Objects::Ground> ground_;
};

#endif