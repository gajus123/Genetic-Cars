//
// \author Jakub Gajownik
// \date 08.03.18
//

#ifndef _GENETIC_CARS_WATCHDOG_H_
#define _GENETIC_CARS_WATCHDOG_H_

#include <QTimer>
#include <QObject>

class Watchdog : public QObject {
	Q_OBJECT
public:
	Watchdog(unsigned int miliseconds);
	~Watchdog();

	void reset();
	void step(unsigned int time);
signals:
	void timeout();
private:
	unsigned int time_left_;
	unsigned int interval_;
};

#endif