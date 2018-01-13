#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include "Track.h"
#include <QFrame>
#include <QTransform>
#include <QPainter>
#include <QPoint>

class SimulationView : public QFrame {
public:
	SimulationView(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
	virtual void paintEvent(QPaintEvent *event);
private:
	void drawTrack(QPainter& painter);
	void drawCar();
	void drawTrackSegment(const std::pair<float, float>& startPoint, const std::pair<float, float>& endPoint, QPainter& painter);

	QTransform transform_;
	Track track_;
};

#endif