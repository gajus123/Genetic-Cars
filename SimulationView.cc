#include "SimulationView.h"

SimulationView::SimulationView(QWidget *parent, Qt::WindowFlags flags) :
	QWidget(parent, flags) {
	transform_.translate(0,0);
}
void SimulationView::paintEvent(QPaintEvent *event) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setTransform(transform_);

	drawTrack(ground_[0], p);
	drawCar(vehicles_[0], p);
}
void SimulationView::drawTrack(const Objects::Ground& track, QPainter& painter) {
	transform_.translate(track.getPosition().x, track.getPosition().y);
	painter.setTransform(transform_);
	std::vector<QPointF> trackPoints;
	for (const auto& point : track.getVertices()) {
		trackPoints.push_back(QPointF(point.x, point.y));
	}
	for (unsigned int i = 1; i < trackPoints.size(); ++i) {
		drawTrackSegment(trackPoints[i - 1], trackPoints[i], painter);
	}

	transform_.translate(-track.getPosition().x, -track.getPosition().y);
}
void SimulationView::drawCar(const Objects::Vehicle& car, QPainter& painter) {
	float angle = (car.getBody().getAngle() / M_PI) * 180.0f;
	Objects::Vector2 position = car.getPosition();

	//Tranform to the center of car
	transform_.translate(position.x, position.y);
	transform_.rotate(angle);
	painter.setTransform(transform_);

	std::vector<QPointF> bodyShape;
	for (const auto& point : car.getBody().getVertices()) {
		bodyShape.emplace_back(std::move(QPointF(point.x, point.y)));
	}
	//Body
	painter.setBrush(QBrush(Qt::green));
	painter.drawPolygon(&bodyShape[0], bodyShape.size());

	transform_.rotate(-angle);
	transform_.translate(-position.x, -position.y);

	//Front wheel
	transform_.translate(car.getFrontWheel().getPosition().x, car.getFrontWheel().getPosition().y);
	painter.setTransform(transform_);

	painter.setBrush(QBrush(QColor(255, 255, 102)));
	painter.drawEllipse(QPointF(0, 0), car.getFrontWheel().getRadius(), car.getFrontWheel().getRadius());

	transform_.translate(-car.getFrontWheel().getPosition().x, -car.getFrontWheel().getPosition().y);

	//Back wheel
	transform_.translate(car.getBackWheel().getPosition().x, car.getBackWheel().getPosition().y);
	painter.setTransform(transform_);

	painter.setBrush(QBrush(QColor(255, 255, 102)));
	painter.drawEllipse(QPointF(0, 0), car.getBackWheel().getRadius(), car.getBackWheel().getRadius());

	transform_.translate(-car.getBackWheel().getPosition().x, -car.getBackWheel().getPosition().y);

	update();
}

void SimulationView::drawTrackSegment(const QPointF& startPoint, const QPointF& endPoint, QPainter& painter) {
	painter.setBrush(QBrush(Qt::black));
	const QPoint points[4] = {
		QPoint(startPoint.x(), startPoint.y()),
		QPoint(endPoint.x(), endPoint.y()),
		QPoint(endPoint.x(), endPoint.y()+10.0f),
		QPoint(startPoint.x(), startPoint.y()+10.0f)
	};
	painter.drawPolygon(points, 4);
}