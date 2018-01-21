/*!
* @authors Jakub Gajownik, Rafa� Galczak
* @date 15.01.18
*
* \brief SimulationView displays Simulation every frame.
*/

#ifndef SIMULATION_VIEW_H
#define SIMULATION_VIEW_H

#include "include/Ground.h"
#include "include/Wheel.h"
#include "include/Vehicle.h"
#include "Simulation.h"
#include <QFrame>
#include <QPainter>
#include <QPoint>
#include <QtMath>
#include <QWidget>
#include <QWheelEvent>
#include <cmath>

class SimulationView : public QFrame {
	const QColor WHEEL_COLOR = QColor(255, 255, 102);
	const QColor BODY_COLOR = Qt::green;
public:
	SimulationView(Simulation& simulation, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
protected:
	virtual void paintEvent(QPaintEvent *event); //!  Displays Simulation world.
	virtual void resizeEvent(QResizeEvent *event); //!  Calculates new scaling value and sets new displaying center point
	virtual void wheelEvent(QWheelEvent * event); //!  Sets new world displaying area
private:
	void drawCar(const Objects::Vehicle& car, QPainter& painter);
	void drawWheel(const Objects::Wheel& wheel, QPainter& painter);
	void drawBody(const Objects::Body& body, QPainter& painter);
	void drawTrack(const Objects::Ground& track, QPainter& painter);
	void drawTrackSegment(const Objects::Vector2& start_point, const Objects::Vector2& end_point, QPainter& painter);

	Simulation& simulation_; //!  Reference to Simulation object
	
	float display_width_; //!  Width of world to be display on screen
	float width_multipier_; //!  World objects coordinates multiplier
	QPointF display_center_; //!  Point of widget which is center of display
};

#endif