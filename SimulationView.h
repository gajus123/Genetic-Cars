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
#include <QWheelEvent>
#include <cmath>

class SimulationView : public QFrame {
public:
	SimulationView(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
	virtual void paintEvent(QPaintEvent *event);
	std::vector<Objects::Ground> ground_;
	std::vector<Objects::Vehicle> vehicles_;
protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual void wheelEvent(QWheelEvent * event);
private:
	void drawTrack(const Objects::Ground& track, QPainter& painter);
	void drawCar(const Objects::Vehicle& car, QPainter& painter);
	void drawWheel(const Objects::Wheel& wheel, QPainter& painter);
	void drawBody(const Objects::Body& body, QPainter& painter);
	void drawTrackSegment(const Objects::Vector2& startPoint, const Objects::Vector2& endPoint, QPainter& painter);

	QTransform transform_;
	
	float display_width_;
	float width_multipier_;
	float display_center_x_;
	float display_center_y_;
};

#endif