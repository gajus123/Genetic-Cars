#include "SimulationView.h"

SimulationView::SimulationView(QWidget *parent, Qt::WindowFlags flags) : QFrame(parent, flags) {
	transform_.translate(10,10);
}
void SimulationView::paintEvent(QPaintEvent *event) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setTransform(transform_);

	drawTrack(p);
}
void SimulationView::drawTrack(QPainter& painter) {
	auto trackPoints = track_.getTrackPoints();
	for (unsigned int i = 1; i < trackPoints.size(); ++i) {
		drawTrackSegment(trackPoints[i - 1], trackPoints[i], painter);
	}
}
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