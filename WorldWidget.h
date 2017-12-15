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