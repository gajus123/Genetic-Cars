#include "include/StatisticView.h"

StatisticView::StatisticView(QWidget *parent, Qt::WindowFlags flags) :
	QChartView(parent) {
	setChart(&chart_);

	series_best_.setName("Najlepszy");
	series_worst_.setName("Najgorszy");
	series_average_.setName("Srednia");
	series_median_.setName("Mediana");

	chart_.addSeries(&series_best_);
	chart_.addSeries(&series_worst_);
	chart_.addSeries(&series_average_);
	chart_.addSeries(&series_median_);

	chart_.createDefaultAxes();
	setRenderHint(QPainter::Antialiasing);

	reset();
}
void StatisticView::addData(float best, float worst, float average, float median) {
	++data_size_;
	current_max_ = std::max(current_max_, best);
	series_best_.append(data_size_, best);
	series_worst_.append(data_size_, worst);
	series_average_.append(data_size_, average);
	series_median_.append(data_size_, median);
	chart_.axisX()->setMax(data_size_);
	chart_.axisY()->setMax(current_max_);
}
void StatisticView::reset() {
	data_size_ = 0;
	series_best_.clear();
	series_worst_.clear();
	series_average_.clear();
	series_median_.clear();

	series_best_.append(0, 0.0);
	series_worst_.append(0, 0.0);
	series_average_.append(0, 0.0);
	series_median_.append(0, 0.0);

	chart_.axisX()->setMax(1);
	chart_.axisY()->setMax(1.0);

	current_max_ = 0.0;
}