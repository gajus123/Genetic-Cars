/*!
* @authors Jakub Gajownik, Rafa³ Galczak
* @date 15.01.18
*
* \brief Statistics responds for calculating stats.
*        As well as being in charge of interacting with other systems using signals (observers).
*/

#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include <algorithm>

class Statistics : public QObject {
	Q_OBJECT

public slots:
	void calculateStatistics(std::vector<float> distances); //!< Brief: Calculates generation stats from distance vector
signals:
	void newValues(float best, float worst, float average, float median); //!< Brief: Sends signal that new generation stats was calculated
};

#endif