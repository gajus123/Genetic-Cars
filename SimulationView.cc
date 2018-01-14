#include "SimulationView.h"

SimulationView::SimulationView(QWidget *parent, Qt::WindowFlags flags) :
	QFrame(parent, flags),
	display_width_(10.0) {
	width_multipier_ = this->width() / display_width_;
}
void SimulationView::paintEvent(QPaintEvent *event) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);

	p.translate(-vehicles_[0].getPosition().x*width_multipier_ + display_center_x_, -vehicles_[0].getPosition().y*width_multipier_ + display_center_y_);
	drawTrack(ground_[0], p);
	drawCar(vehicles_[0], p);
	p.translate(vehicles_[0].getPosition().x, vehicles_[0].getPosition().y);
}
void SimulationView::drawTrack(const Objects::Ground& track, QPainter& painter) {
	painter.save();
	painter.translate(track.getPosition().x*width_multipier_, track.getPosition().y*width_multipier_);
	auto trackPoints = track.getVertices();
	for (unsigned int i = 1; i < track.getVertices().size(); ++i) {
		drawTrackSegment(trackPoints[i - 1], trackPoints[i], painter);
	}
	painter.restore();
}
void SimulationView::resizeEvent(QResizeEvent *event) {
	width_multipier_ = this->width() / display_width_;

	display_center_x_ = this->width() * 0.5f;
	display_center_y_ = this->height() * 0.66f;
}
void SimulationView::wheelEvent(QWheelEvent * event) {
	display_width_ -= event->delta() / 120;
	resizeEvent(nullptr);
}
void SimulationView::drawCar(const Objects::Vehicle& car, QPainter& painter) {
	painter.save();
	painter.translate(car.getPosition().x*width_multipier_, car.getPosition().y*width_multipier_);
	drawBody(car.getBody(), painter);
	painter.restore();

	drawWheel(car.getFrontWheel(), painter);
	drawWheel(car.getBackWheel(), painter);

	update();
}
void SimulationView::drawWheel(const Objects::Wheel& wheel, QPainter& painter) {
	painter.save();
	painter.translate(wheel.getPosition().x*width_multipier_, wheel.getPosition().y*width_multipier_);

	painter.setBrush(QBrush(QColor(255, 255, 102)));
	painter.drawEllipse(QPointF(0, 0), wheel.getRadius()*width_multipier_, wheel.getRadius()*width_multipier_);

	painter.rotate(-wheel.getAngle() / M_PI*180.0f);
	painter.drawLine(0, 0, wheel.getRadius()*width_multipier_, 0);
	painter.rotate(wheel.getAngle() / M_PI*180.0f);

	painter.restore();
}
void SimulationView::drawBody(const Objects::Body& body, QPainter& painter) {
	painter.rotate(body.getAngle() / M_PI * 180.0f);

	std::vector<QPointF> bodyShape;
	for (const auto& point : body.getVertices()) {
		bodyShape.emplace_back(std::move(QPointF(point.x*width_multipier_, point.y*width_multipier_)));
	}

	painter.setBrush(QBrush(Qt::green));
	painter.drawPolygon(&bodyShape[0], bodyShape.size());

}

void SimulationView::drawTrackSegment(const Objects::Vector2& startPoint, const Objects::Vector2& endPoint, QPainter& painter) {
	painter.setBrush(QBrush(Qt::black));
	const QPoint points[4] = {
		QPoint(startPoint.x*width_multipier_, startPoint.y*width_multipier_),
		QPoint(endPoint.x*width_multipier_, endPoint.y*width_multipier_),
		QPoint(endPoint.x*width_multipier_, (endPoint.y+0.05f)*width_multipier_),
		QPoint(startPoint.x*width_multipier_, (startPoint.y+0.05f)*width_multipier_)
	};
	painter.drawPolygon(points, 4);
}