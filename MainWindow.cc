#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), world_widget_(this) {
	setObjectName("GeneticCars");
	setWindowTitle("Genetic Cars"); 
	setCentralWidget(&world_widget_);
	resize(WINDOW_WIDTH, WINDOW_HEIGHT);
	world_widget_.start();
}