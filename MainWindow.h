/*!
 * @authors Jakub Gajownik, Rafał Galczak
 * @date 14.12.17
 *
 * \brief MainWindow setups view and application window structure.
 *        As well as being in charge of interacting with user.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "WorldWidget.h"
#include "SimulationView.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QGroupBox>
#include <QtCharts>

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
    const int WINDOW_WIDTH = 500;
    const int WINDOW_HEIGHT = 500;

	MainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
private:
	void setupSimulationInterface();
	void setupFileInterface();
	void setupAlgorithmInterface();

	WorldWidget world_widget_; //!< Brief: Setups physics and objects for the example
	SimulationView simulation_view_;

	//UI
	QWidget central_widget_;

	//Simulation interface
	QGroupBox simulation_group_;
	QPushButton reset_button_;
	QPushButton pause_button_;
	QToolButton speed_increase_button_;
	QToolButton speed_decrease_button_;
	QLabel speed_label_;
	QLabel cars_count_label_;
	QLineEdit cars_count_edit_;

	//File interface
	QGroupBox file_group_;
	QPushButton load_button_;
	QPushButton save_button_;

	//Genetic algorithm
	QGroupBox algorithm_group_;
	QLabel mutation_size_label_;
	QLineEdit mutation_size_edit_;
	QLabel mutation_rate_label_;
	QLineEdit mutation_rate_edit_;
};

#endif