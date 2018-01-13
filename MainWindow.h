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

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
    const int WINDOW_WIDTH = 500;
    const int WINDOW_HEIGHT = 500;

	MainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
private:
	WorldWidget world_widget_; //!< Brief: Setups physics and objects for the example
	SimulationView simulation_view_;
};

#endif