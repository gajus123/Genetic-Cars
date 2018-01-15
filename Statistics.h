#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include <cstdio>
#include <algorithm>

class Statistics : public QObject{
	Q_OBJECT

public slots:
	void calculateStatistics(std::vector<float> distances);
signals:
	void newValues(float best, float worst, float average, float median);
};

#endif