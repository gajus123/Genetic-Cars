#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include "Track.h"
#include "Car.h"
#include "include\Ground.h"
#include "include\Wheel.h"
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
	void drawCar(QPainter& painter);
	//void drawWheel(const b2Vec2& position, QPainter& painter);
	void drawTrackSegment(const std::pair<float, float>& startPoint, const std::pair<float, float>& endPoint, QPainter& painter);

	QTransform transform_;
	Track track_;
	Objects::Ground ground_;
	Objects::Wheel wheel_;
};

#endif