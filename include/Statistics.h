//
// \authors Jakub Gajownik
// \date 15.01.18
//

#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include <algorithm>

/*!
	\class Simulation
	\brief Responds for calculating stats as well as being in charge of interacting with other systems using signals (observers).
*/
class Statistics : public QObject {
	Q_OBJECT

public slots:
	void calculateStatistics(std::vector<float> distances); //!  Calculates generation stats from distance vector
signals:
	void newValues(float best, float worst, float average, float median); //!  Sends signal that new generation stats was calculated
};

#endif