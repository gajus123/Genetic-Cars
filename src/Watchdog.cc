#include <Watchdog.h>


Watchdog::Watchdog(unsigned int miliseconds) : 
	QObject(),
	interval_(miliseconds),
	time_left_(miliseconds) {

}

Watchdog::~Watchdog() {

}

void Watchdog::reset() {
	time_left_ = interval_;
}

void Watchdog::step(unsigned int time) {
	if (time < time_left_)
		time_left_ -= time;
	else {
		unsigned int time_reserve = time - time_left_;
		time_left_ = interval_ - time_reserve;
		emit timeout();
	}
}