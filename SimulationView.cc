#include "SimulationView.h"

SimulationView::SimulationView(Simulation& simulation, QWidget *parent, Qt::WindowFlags flags) :
	simulation_(simulation),
	QFrame(parent, flags),
	display_width_(30.0) {

	width_multipier_ = this->width() / display_width_;
}
void SimulationView::paintEvent(QPaintEvent *event) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);

	const std::vector<Objects::Vehicle> vehicles = simulation_.getVehicles();
	if (vehicles.size() != 0) {
		const Objects::Vehicle& best_vehicle = simulation_.getBestVehicle();
		p.translate(-best_vehicle.getPosition().x*width_multipier_ + display_center_.x(), -best_vehicle.getPosition().y*width_multipier_ + display_center_.y());
	}
	if (auto sim = simulation_.getGround().lock()) {
		drawTrack(*sim.get(), p);
	}
	for (const auto& vehicle : vehicles) {
		drawCar(vehicle, p);
	}

	update();
}
void SimulationView::drawTrack(const Objects::Ground& track, QPainter& painter) {
	painter.save();
	painter.translate(track.getPosition().x*width_multipier_, track.getPosition().y*width_multipier_);
	auto track_points = track.getVertices();
	for (unsigned int i = 1; i < track.getVertices().size(); ++i) {
		drawTrackSegment(track_points[i - 1], track_points[i], painter);
	}
	painter.restore();
}
void SimulationView::resizeEvent(QResizeEvent *event) {
	width_multipier_ = this->width() / display_width_;

	display_center_.setX(this->width() * 0.5f);
	display_center_.setY(this->height() * 0.66f);
}
void SimulationView::wheelEvent(QWheelEvent * event) {
	display_width_ -= event->delta() / 120;
	display_width_ = std::max(display_width_, 2.0f);
	resizeEvent(nullptr);
}
void SimulationView::drawCar(const Objects::Vehicle& car, QPainter& painter) {
	painter.save();
	painter.translate(car.getPosition().x*width_multipier_, car.getPosition().y*width_multipier_);
	drawBody(car.getBody(), painter);
	painter.restore();

	drawWheel(car.getFrontWheel(), painter);
	drawWheel(car.getBackWheel(), painter);
}
void SimulationView::drawWheel(const Objects::Wheel& wheel, QPainter& painter) {
	painter.save();
	painter.translate(wheel.getPosition().x*width_multipier_, wheel.getPosition().y*width_multipier_);

	painter.setBrush(QBrush(WHEEL_COLOR));
	painter.drawEllipse(QPointF(0, 0), wheel.getRadius()*width_multipier_, wheel.getRadius()*width_multipier_);

	painter.rotate(-wheel.getAngle() / M_PI*180.0f);
	painter.drawLine(0, 0, wheel.getRadius()*width_multipier_, 0);

	painter.restore();
}
void SimulationView::drawBody(const Objects::Body& body, QPainter& painter) {
	painter.save();

	painter.rotate(body.getAngle() / M_PI * 180.0f);

	std::vector<QPointF> body_shape;
	for (const auto& point : body.getVertices()) {
		body_shape.emplace_back(std::move(QPointF(point.x*width_multipier_, point.y*width_multipier_)));
	}

	painter.setBrush(QBrush(BODY_COLOR));
	painter.drawPolygon(&body_shape[0], body_shape.size());

	painter.restore();
}

void SimulationView::drawTrackSegment(const Objects::Vector2& start_point, const Objects::Vector2& end_point, QPainter& painter) {
	painter.setBrush(QBrush(Qt::black));
	const QPoint points[4] = {
		QPoint(start_point.x*width_multipier_, start_point.y*width_multipier_),
		QPoint(end_point.x*width_multipier_, end_point.y*width_multipier_),
		QPoint(end_point.x*width_multipier_, (end_point.y+0.05f)*width_multipier_),
		QPoint(start_point.x*width_multipier_, (start_point.y+0.05f)*width_multipier_)
	};
	painter.drawPolygon(points, 4);
}