#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include "include\Ground.h"
#include "include\Wheel.h"
#include "include\Vehicle.h"
#include "include\ObjectsFactory.h"
#include "Simulation.h"
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
	const QColor WHEEL_COLOR = QColor(255, 255, 102);
public:
	SimulationView(Simulation& simulation, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *event);
	virtual void wheelEvent(QWheelEvent * event);
private:
	void drawCar(const Objects::Vehicle& car, QPainter& painter);
	void drawWheel(const Objects::Wheel& wheel, QPainter& painter);
	void drawBody(const Objects::Body& body, QPainter& painter);
	void drawTrack(const Objects::Ground& track, QPainter& painter);
	void drawTrackSegment(const Objects::Vector2& startPoint, const Objects::Vector2& endPoint, QPainter& painter);

	Simulation& simulation_;
	
	float display_width_;
	float width_multipier_;
	float display_center_x_;
	float display_center_y_;
};

#endif