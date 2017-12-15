#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QPainter>
#include <Box2D/Box2D.h>
#include <iostream>

class WorldWidget : public QWidget {
	struct Ball
	{
		b2Body *body_;
		b2Fixture *fixture_;
	};
public:
	const float GRAVITY_X = 0.0f;
	const float GRAVITY_Y = -10.0f;
	const int NUMBER_OF_BALLS = 30;
	const float SCALE_X = 10.0f;
	const float SCALE_Y = -10.0f;
	const float TRANSLATE_X = 0.0f;
	const float TRANSLATE_Y = -64.0f;
	const int BALLS_MAX_DISTANCE_X = 36;
	const int BALLS_MAX_DISTANCE_Y = 2;
	const float BALL_RADIUS = 1.0f;
	const float BALL_STARTING_Y = 62.0f;
	const float BALL_DENSITY = 1.0f;
	const float BALL_FRICTION = 1.0f;
	const float BALL_RESTITUATION = 0.6f;
	const float WORLD_STEP = 1.0f/60.0f;
	const int FRAME_TIME = 1000/60;
	const int VELOCITY_ITERATIONS = 8;
	const int POSITION_ITERATIONS = 3;
	
	WorldWidget(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
	WorldWidget(const WorldWidget&) = delete;
	WorldWidget& operator=(const WorldWidget&) = delete;
	~WorldWidget();
	
	void start();
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void timerEvent(QTimerEvent *event);
private:
	void drawEllipse(QPainter &p, const Ball& o);
	Ball createBall(const b2Vec2& pos, float32 radius);
	
	b2World *world_;
    int timerId_;
    QTransform transform_;
    QVector<Ball> balls_;
};

#endif