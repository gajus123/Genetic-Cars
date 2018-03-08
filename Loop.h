//
// \author Jakub Gajownik
// \date 13.01.18
//

#ifndef GENETIC_CARS_PHYSICS_H
#define GENETIC_CARS_PHYSICS_H

#include <QTimer>
#include <QObject>
#include <iostream>


namespace Physics {

	const int PHYSICS_FRAME_TIME = 16;

	/*!
		\class Loop
		\brief Physics loop objec

		Loop wraps Box2D world creation and simulation computing.
		It is advised that all constructor parameters should remain default.
		
		After creation call start() to start simulation.
		Call stop() to pause, a simulation.
	*/
    class Loop : public QObject {
		Q_OBJECT

    public:
        Loop();
        Loop(const Loop&) = delete;
        Loop& operator=(const Loop&) = delete;

		void start(); //!  Starts a physics simulation
        void stop(); //!  Pauses a physisc simulation
		void setTimeSpeed(float time_speed); //!  Sets time speed multiplier - 1.0 is normal speed
	signals:
		void step(unsigned int time);
	private slots:
		void update(); //!  Performs single physics loop iteration
    private:
		QTimer timer_;
		unsigned int interval_;
    };

}
#endif //GENETIC_CARS_PHYSICS_H
