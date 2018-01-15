#ifndef STATISTICVIEW_H
#define STATISTICVIEW_H

#include <QtCharts>

class StatisticView : public QChartView {
	Q_OBJECT
public:
	StatisticView(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
public slots:
	void addData(float best, float worst, float average, float median);
	void reset();
private:
	QChart chart_;
	QLineSeries series_best_;
	QLineSeries series_worst_;
	QLineSeries series_average_;
	QLineSeries series_median_;
	unsigned int data_size_;
	float current_max_;
};

#endif