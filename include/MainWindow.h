//
// \authors Jakub Gajownik
// \date 15.01.18
//

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

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
#include <iostream>
#include <QShortcut>

#include <SimulationView.h>
#include <StatisticView.h>
#include <Simulation.h>
#include <Statistics.h>
#include <Loop.h>
#include <algorithm/PopulationWrapper.h>

namespace Ui {
    class MainWindow;
}

/*!
	\class MainWindow
	\brief Main user interface class
	Setups view and application window structure.
	MainWindow manages all widgets and their actions.
	
	After creation call show() to diplay App window.
*/
class MainWindow : public QMainWindow {
	Q_OBJECT
public:
    const int WINDOW_WIDTH = 500;
    const int WINDOW_HEIGHT = 500;

	MainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
private slots:
	void resetSimulation(); //!  Resets whole simulation and genetic algorithm.
	void eliteSpecimenNumberChanged(); //!  Reacts to change of mutation rate edit line.
	void mutationSizeChanged();//!  Reacts to change of mutation size edit line.
	void saveToFile(); //!  Reacts to 'Save' button clicks.
	void loadFromFile(); //!  Reacts to 'Load' button clicks.
	void pauseSimulation(bool paused); //!  Pauses physics and simulation.
	void carsNumberChanged(); //!  Changes cars number in simulation if writted text is number.
	void speedChanged(); //!  Changes speed simulation to the selected one.
private:
	void initializeSpeedWidget(); //!  Fill speed selection combo box
	void pauseSimulation();
	void resumeSimulation();

	Physics::Loop loop_;
	Algorithm2::PopulationWrapper population_;
	Simulation simulation_;
	Statistics statistics_;

	StatisticView statistic_view_;
	SimulationView simulation_view_;

	Ui::MainWindow* ui_;

	QShortcut pause_action_;
};

#endif