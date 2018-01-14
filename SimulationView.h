#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include "Track.h"
#include "Car.h"
#include "include\Ground.h"
#include "include\Wheel.h"
#include "include\Vehicle.h"
#include "include\ObjectsFactory.h"
#include <QFrame>
#include <QTransform>
#include <QPainter>
#include <QPoint>
#include <QDebug>
#include <QtMath>
#include <QWidget>
#include <QGLWidget>

class SimulationView : public QFrame {
public:
	SimulationView(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
	virtual void paintEvent(QPaintEvent *event);
	std::vector<Objects::Ground> ground_;
	std::vector<Objects::Vehicle> vehicles_;
private:
	void drawTrack(const Objects::Ground& track, QPainter& painter);
	void drawCar(const Objects::Vehicle& car, QPainter& painter);
	void drawTrackSegment(const QPointF& startPoint, const QPointF& endPoint, QPainter& painter);

	QTransform transform_;
	Track track_;
};

#endif