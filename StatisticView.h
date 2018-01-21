//
// \author Jakub Gajownik
// \date 15.01.18
//

#ifndef STATISTICVIEW_H
#define STATISTICVIEW_H

#include <QChart>
#include <QChartView>
#include <QLineSeries>

QT_CHARTS_USE_NAMESPACE

/*!
	\brief StatisticView responds for displaying chart of collected stats.
	As well as being in charge of interacting with other systems using signals (observers).
*/
class StatisticView : public QChartView {
	Q_OBJECT
public:
	StatisticView(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
public slots:
	void addData(float best, float worst, float average, float median); //!  Adds new generation result into the history
	void reset(); //!  Resets history
private:
	QChart chart_; //!  Manages the graphical representation of chart
	QLineSeries series_best_; //!  Contains best unit result history
	QLineSeries series_worst_; //!  Contains worst unit result history
	QLineSeries series_average_; //!  Contains average result history
	QLineSeries series_median_; //!  Contains median of the units result history
	unsigned int data_size_; //!  Current history length
	float current_max_; //!  Current maximum value in whole history
};

#endif