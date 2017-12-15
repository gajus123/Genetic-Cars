#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QPushButton>

class MainWindow : public QMainWindow {
	Q_OBJECT
	
public:
		MainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
		MainWindow(const MainWindow&) = delete;
		MainWindow& operator=(const MainWindow&) = delete;
public slots:
		void dupa();
private:
	QPushButton button;
};

#endif