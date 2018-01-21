/*!
 * @authors Jakub Gajownik, Rafał Galczak
 * @date 15.01.18
 *
 * \brief MainWindow setups view and application window structure.
 *        As well as being in charge of interacting with user.
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "Population.h"
#include "SimulationView.h"
#include "StatisticView.h"
#include "Simulation.h"
#include "Statistics.h"
#include "Loop.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QGroupBox>
#include <QFileDialog>
#include <QComboBox>

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
    const int WINDOW_WIDTH = 500;
    const int WINDOW_HEIGHT = 500;

	MainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
private slots:
	void resetSimulation(); //!< Brief: Resets whole simulation and genetic algorithm.
	void eliteSpecimenNumberChanged(); //!< Brief: Reacts to change of mutation rate edit line.
	void mutationSizeChanged();//!< Brief: Reacts to change of mutation size edit line.
	void saveToFile(); //!< Brief: Reacts to 'Save' button clicks.
	void loadFromFile(); //!< Brief: Reacts to 'Load' button clicks.
	void pauseSimulation(bool paused); //!< Brief: Pauses physics and simulation.
	void carsNumberChanged(); //!< Brief: Changes cars number in simulation if writted text is number.
	void speedChanged(); //!< Brief: Changes speed simulation to the selected one.
private:
	QWidget* createSimulationWidgets(); //!< Brief: Creates GUI part responsible for Simulation settings manipulation/displaying. Return pointer to widgets container.
	QWidget* createFileWidgets(); //!< Brief: Creates GUI part responsible for saving/loading buttons. Return pointer to widgets container.
	QWidget* createAlgorithmWidgets(); //!< Brief: Creates GUI part responsible for Algorithm settings manipulation/displaying. Return pointer to widgets container.
	void initializeSpeedWidget();
	void pauseSimulation();
	void resumeSimulation();

	template<class WidgetType, class LayoutType>
	std::tuple<WidgetType*, LayoutType*> createLayout(QLayout* parent_layout = Q_NULLPTR); //!< Brief: Creates container of WidgetType, sets its layout to new LayoutType object.
																						   //!<		   If parent_layout is not Q_NULLPTR, it also adds container into parent_layout.
																						   //!<		   Returns tuple of pointers of created container and layout.

	Physics::Loop loop_;
	Algorithm::Population population_;
	Simulation simulation_;
	Statistics statistics_;

	StatisticView statistic_view_;
	SimulationView simulation_view_;

	QPushButton reset_button_;
	QPushButton pause_button_;
	QComboBox simulation_speed_chooser_;
	QLabel cars_count_label_;
	QLineEdit cars_count_edit_;

	QGroupBox file_group_;
	QPushButton load_button_;
	QPushButton save_button_;

	QLabel mutation_size_label_;
	QLineEdit mutation_size_edit_;
	QLabel elite_specimen_number_label_;
	QLineEdit elite_specimen_number_edit_;
};

#endif