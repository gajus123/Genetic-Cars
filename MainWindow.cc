/*!
 * @authors Jakub Gajownik, Rafał Galczak
 * @date 14.12.17
 *
 */
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), world_widget_(this) {
	setObjectName("GeneticCars");
	setWindowTitle("Genetic Cars"); 

	setupSimulationInterface();
	setupFileInterface();
	setupAlgorithmInterface();

	QVBoxLayout* layout = new QVBoxLayout();
	setCentralWidget(&central_widget_);
	central_widget_.setLayout(layout);

	layout->addWidget(&simulation_group_);
	layout->addWidget(&file_group_);
	layout->addWidget(&algorithm_group_);



	/*setCentralWidget(&simulation_group_);
	QVBoxLayout* layout = new QVBoxLayout();
	
	simulation_group_.setTitle("Symulacja");
	simulation_group_.setLayout(layout);

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
	cars_count_label_.setText("Ilość pojazdów:");*/

	//setCentralWidget(&world_widget_);
	//setCentralWidget(&simulation_view_);
	//setCentralWidget(&reset_button_);
	//resize(WINDOW_WIDTH, WINDOW_HEIGHT);
	world_widget_.start();
}
void MainWindow::setupSimulationInterface() {
	QVBoxLayout* layout = new QVBoxLayout();

	simulation_group_.setTitle("Symulacja");
	simulation_group_.setLayout(layout);

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
}
void MainWindow::setupFileInterface() {
	QHBoxLayout* layout = new QHBoxLayout();
	
	file_group_.setTitle("Zapis/odczyt");
	file_group_.setLayout(layout);

	layout->addWidget(&load_button_);
	layout->addWidget(&save_button_);

	load_button_.setText("Wczytaj");
	save_button_.setText("Zapisz");
}
void MainWindow::setupAlgorithmInterface() {
	QHBoxLayout* layout = new QHBoxLayout();

	algorithm_group_.setTitle("Parametry algorytmu genetycznego");
	algorithm_group_.setLayout(layout);

	QWidget* labelsWidget = new QWidget();
	QVBoxLayout* labelsLayout = new QVBoxLayout();
	labelsWidget->setLayout(labelsLayout);

	labelsLayout->addWidget(&mutation_size_label_);
	labelsLayout->addWidget(&mutation_rate_label_);

	QWidget* editsWidget = new QWidget();
	QVBoxLayout* editsLayout = new QVBoxLayout();
	editsWidget->setLayout(editsLayout);

	editsLayout->addWidget(&mutation_size_edit_);
	editsLayout->addWidget(&mutation_rate_edit_);


	mutation_size_label_.setText("Prawdopodobieństwo mutacji:");
	mutation_rate_label_.setText("Współczynnik mutacji:");

	layout->addWidget(labelsWidget);
	layout->addWidget(editsWidget);
}