#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), button(this) {
	connect(&button, SIGNAL(pressed()), this, SLOT(dupa()));
	setCentralWidget(&button);
	setObjectName("MainWindow");
}
void MainWindow::dupa()
{
	std::cout << "Dupa\n";
}