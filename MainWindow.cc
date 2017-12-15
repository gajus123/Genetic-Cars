#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), world_widget_(this) {
	setObjectName("GeneticCars");
	setWindowTitle("Genetic Cars"); 
	setCentralWidget(&world_widget_);
	resize(window_width, window_height);
	world_widget_.start();
}