#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "WorldWidget.h"
#include <QMainWindow>

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
    const int WINDOW_WIDTH = 500;
    const int WINDOW_HEIGHT = 500;

	MainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete
private:
	WorldWidget world_widget_;	
};

#endif