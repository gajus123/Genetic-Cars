#include "SimulationView.h"

SimulationView::SimulationView(QWidget *parent, Qt::WindowFlags flags) :
	QFrame(parent, flags),
	ground_(Objects::Vector2(0, 0), 5.0f, { 0.0f, 1.0f, 0.0f, 3.0f }),
	wheel(Objects::Vector2(1, 0), 1) {
	transform_.translate(10,10);
}
void SimulationView::paintEvent(QPaintEvent *event) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setTransform(transform_);

	drawTrack(p);
	drawCar(p);
}
void SimulationView::drawTrack(QPainter& painter) {
	auto trackPoints = track_.getTrackPoints();
	for (unsigned int i = 1; i < trackPoints.size(); ++i) {
		drawTrackSegment(trackPoints[i - 1], trackPoints[i], painter);
	}
}
void SimulationView::drawCar(QPainter& painter) {
	Car car;

	//Tranform to the center of car
	transform_.translate(car.getPosition().first, car.getPosition().second);
	painter.setTransform(transform_);

	//Body
	painter.setBrush(QBrush(Qt::green));
	std::vector<QPoint> carBody;
	for (const auto& point : car.getShapePoints()) {
		carBody.push_back(QPoint(point.first,point.second));
	}
	painter.drawPolygon(&carBody[0], car.getShapePoints().size());

	//Wheels
	painter.setBrush(QBrush(QColor(255,255,102)));
	for (const auto& wheel : car.getWheels()) {
		painter.drawEllipse(QPointF(wheel.first.first, wheel.first.second), wheel.second, wheel.second);
	}

	//Transform to the previous position
	transform_.translate(-car.getPosition().first, -car.getPosition().second);
	painter.setTransform(transform_);
}
/*void SimulationView::drawWheel(const b2Vec2& position, QPainter& painter) {
	painter.setBrush(QBrush(QColor(255, 255, 102)));
	painter.drawEllipse(QPointF(wheel.first.first, wheel.first.second), wheel.second, wheel.second);
}*/
void SimulationView::drawTrackSegment(const std::pair<float, float>& startPoint, const std::pair<float, float>& endPoint, QPainter& painter) {
	painter.setBrush(QBrush(Qt::black));
	const QPoint points[4] = {
		QPoint(startPoint.first, startPoint.second),
		QPoint(endPoint.first, endPoint.second),
		QPoint(endPoint.first, endPoint.second-10.0f),
		QPoint(startPoint.first, startPoint.second-10.0f)
	};
	painter.drawPolygon(points, 4);
}