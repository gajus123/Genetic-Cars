/*!
* @authors Jakub Gajownik, Rafa� Galczak
* @date 15.01.18
*
* \brief StatisticView responds for displaying chart of collected stats.
*        As well as being in charge of interacting with other systems using signals (observers).
*/

#ifndef STATISTICVIEW_H
#define STATISTICVIEW_H

#include <QChart>
#include <QChartView>
#include <QLineSeries>

QT_CHARTS_USE_NAMESPACE

class StatisticView : public QChartView {
	Q_OBJECT
public:
	StatisticView(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
public slots:
	void addData(float best, float worst, float average, float median); //!< Brief: Adds new generation result into the history
	void reset(); //!< Brief: Resets history
private:
	QChart chart_; //!< Brief: Manages the graphical representation of chart
	QLineSeries series_best_; //!< Brief: Contains best unit result history
	QLineSeries series_worst_; //!< Brief: Contains worst unit result history
	QLineSeries series_average_; //!< Brief: Contains average result history
	QLineSeries series_median_; //!< Brief: Contains median of the units result history
	unsigned int data_size_; //!< Brief: Current history length
	float current_max_; //!< Brief: Current maximum value in whole history
};

#endif