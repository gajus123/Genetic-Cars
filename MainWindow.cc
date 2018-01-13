/*!
 * @authors Jakub Gajownik, Rafał Galczak
 * @date 14.12.17
 *
 */
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), world_widget_(this) {
	setObjectName("GeneticCars");
	setWindowTitle("Genetic Cars"); 

	setCentralWidget(&central_widget_);
	QVBoxLayout* layout = new QVBoxLayout();
	central_widget_.setLayout(layout);

	layout->addWidget(&reset_button_);
	layout->addWidget(&pause_button_);
	
	//Speed
	QHBoxLayout* speedLayout = new QHBoxLayout();
	QGroupBox* speedContainer = new QGroupBox();
	speedContainer->setLayout(speedLayout);
	speedContainer->setTitle("Prędkość symulacji");

	layout->addWidget(speedContainer);

	speedLayout->addWidget(&speed_decrease_button_);
	speedLayout->addWidget(&speed_label_);
	speedLayout->addWidget(&speed_increase_button_);

	//Cars
	QHBoxLayout* carsLayout = new QHBoxLayout();
	QWidget* carsContainer = new QWidget();
	carsContainer->setLayout(carsLayout);

	layout->addWidget(carsContainer);

	carsLayout->addWidget(&cars_count_label_);
	carsLayout->addWidget(&cars_count_edit_);

	reset_button_.setText("Resetuj");
	pause_button_.setText("Pauza");
	speed_decrease_button_.setText("-");
	speed_increase_button_.setText("+");
	speed_label_.setText("10");
	speed_label_.setAlignment(Qt::AlignCenter);
	cars_count_label_.setText("Ilość pojazdów:");

	//setCentralWidget(&world_widget_);
	//setCentralWidget(&simulation_view_);
	//setCentralWidget(&reset_button_);
	//resize(WINDOW_WIDTH, WINDOW_HEIGHT);
	world_widget_.start();
}