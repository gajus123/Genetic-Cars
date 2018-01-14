#include "SimulationView.h"

SimulationView::SimulationView(QWidget *parent, Qt::WindowFlags flags) :
	QFrame(parent, flags) {
}
void SimulationView::paintEvent(QPaintEvent *event) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);

	p.translate(-vehicles_[0].getPosition().x*100+200, -vehicles_[0].getPosition().y*100+200);
	drawTrack(ground_[0], p);
	drawCar(vehicles_[0], p);
	p.translate(vehicles_[0].getPosition().x, vehicles_[0].getPosition().y);
}
void SimulationView::drawTrack(const Objects::Ground& track, QPainter& painter) {
	painter.save();

	painter.translate(track.getPosition().x*100, track.getPosition().y*100);
	std::vector<QPointF> trackPoints;
	for (const auto& point : track.getVertices()) {
		trackPoints.push_back(QPointF(point.x*100, point.y*100));
	}
	for (unsigned int i = 1; i < trackPoints.size(); ++i) {
		drawTrackSegment(trackPoints[i - 1], trackPoints[i], painter);
	}

	painter.restore();
}
void SimulationView::drawCar(const Objects::Vehicle& car, QPainter& painter) {
	float angle = (car.getBody().getAngle() / M_PI) * 180.0f;
	Objects::Vector2 position = car.getPosition();

	//Tranform to the center of car
	painter.save();
	painter.translate(position.x*100, position.y*100);
	painter.rotate(angle);

	std::vector<QPointF> bodyShape;
	for (const auto& point : car.getBody().getVertices()) {
		bodyShape.emplace_back(std::move(QPointF(point.x*100, point.y*100)));
	}
	//Body
	painter.setBrush(QBrush(Qt::green));
	painter.drawPolygon(&bodyShape[0], bodyShape.size());

	painter.restore();

	//Front wheel
	painter.save();
	painter.translate(car.getFrontWheel().getPosition().x*100, car.getFrontWheel().getPosition().y*100);

	painter.setBrush(QBrush(QColor(255, 255, 102)));
	painter.drawEllipse(QPointF(0, 0), car.getFrontWheel().getRadius()*100, car.getFrontWheel().getRadius()*100);


	painter.restore();

	//Back wheel
	painter.save();
	painter.translate(car.getBackWheel().getPosition().x*100, car.getBackWheel().getPosition().y*100);

	painter.setBrush(QBrush(QColor(255, 255, 102)));
	painter.drawEllipse(QPointF(0, 0), car.getBackWheel().getRadius()*100, car.getBackWheel().getRadius()*100);

	painter.rotate(-car.getBackWheel().getAngle() / M_PI*180.0f);
	painter.drawLine(0, 0, car.getBackWheel().getRadius()*100, 0);
	painter.rotate(car.getBackWheel().getAngle() / M_PI*180.0f);

	painter.restore();

	update();
}

void SimulationView::drawTrackSegment(const QPointF& startPoint, const QPointF& endPoint, QPainter& painter) {
	painter.setBrush(QBrush(Qt::black));
	const QPoint points[4] = {
		QPoint(startPoint.x(), startPoint.y()),
		QPoint(endPoint.x(), endPoint.y()),
		QPoint(endPoint.x(), endPoint.y()+0.01f),
		QPoint(startPoint.x(), startPoint.y()+0.01f)
	};
	painter.drawPolygon(points, 4);
}