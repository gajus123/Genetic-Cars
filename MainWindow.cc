/*!
 * @authors Jakub Gajownik, Rafał Galczak
 * @date 14.12.17
 *
 */
#include "MainWindow.h"
#include "include/GroundGenerator.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
	QMainWindow(parent, flags),
	simulation_(),
	simulation_view_(simulation_) {
	setObjectName("GeneticCars");
	setWindowTitle("Genetic Cars"); 


	QWidget* content = new QWidget();
	QVBoxLayout* contentLayout = new QVBoxLayout();
	content->setLayout(contentLayout);

	statistic_view_.addData(1.0, 0.5, 0.2, 0.3);
	statistic_view_.addData(2.0, 1.0, 0.6, 0.65);
	statistic_view_.reset();
	statistic_view_.addData(0.5, 0.1, 0.3, 0.2);

	QSizePolicy simulationViewPolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	simulationViewPolicy.setVerticalStretch(3);
	simulation_view_.setSizePolicy(simulationViewPolicy);
	contentLayout->addWidget(&simulation_view_);
	QSizePolicy statisticViewPolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	statisticViewPolicy.setVerticalStretch(2);
	statistic_view_.setSizePolicy(statisticViewPolicy);
	contentLayout->addWidget(&statistic_view_);

	QWidget* centralWidget = new QWidget(this);
	QHBoxLayout* centralLayout = new QHBoxLayout();
	setCentralWidget(centralWidget);
	centralWidget->setLayout(centralLayout);


	centralLayout->addWidget(content);
	centralLayout->addWidget(&sidebar_widget_);

	//Sidebar setup
	centralLayout->setAlignment(&sidebar_widget_, Qt::AlignTop);

	setupSimulationInterface();
	setupFileInterface();
	setupAlgorithmInterface();

	QVBoxLayout* sidebar_layout = new QVBoxLayout();
	sidebar_widget_.setLayout(sidebar_layout);

	sidebar_widget_.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	sidebar_layout->addWidget(&simulation_group_);
	sidebar_layout->addWidget(&file_group_);
	sidebar_layout->addWidget(&algorithm_group_);

	connect(&mutation_rate_edit_, SIGNAL(editingFinished()), this, SLOT(mutationRateChanged()));
	connect(&mutation_size_edit_, SIGNAL(editingFinished()), this, SLOT(mutationSizeChanged()));
	connect(&load_button_, SIGNAL(clicked()), this, SLOT(loadFromFile()));
	connect(&save_button_, SIGNAL(clicked()), this, SLOT(saveToFile()));
	connect(&reset_button_, SIGNAL(clicked()), &simulation_, SLOT(reset()));
	connect(&pause_button_, SIGNAL(toggled(bool)), this, SLOT(pauseSimulation(bool)));
	connect(&cars_count_edit_, SIGNAL(editingFinished()), this, SLOT(carsNumberChanged()));

	Physics::ObjectsFactory::init(loop_);
	simulation_view_.vehicles_.push_back(Objects::Vehicle(Objects::Vector2(0, 0.4), {0.2f, 0.2f, 0.5f, 0.28f, 0.2f, 0.28f, 0.5f, 0.2f}, 0.35f, 0.35f));

	simulation_.newGround();
	simulation_.newVehicles();
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
	pause_button_.setCheckable(true);
	//pause_button_.setChecked(true);
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
void MainWindow::mutationRateChanged() {
	bool number;
	float temp = mutation_rate_edit_.text().toFloat(&number);
	if (number)
		qDebug() << "Rate";
}
void MainWindow::mutationSizeChanged() {
	bool number;
	float temp = mutation_rate_edit_.text().toFloat(&number);
	if (number)
		qDebug() << "Size";
}
void MainWindow::saveToFile() {
	QString fileName = QFileDialog::getSaveFileName(this,
		"Save Population", "",
		"Text Files (*.txt);;All Files (*)");
}
void MainWindow::loadFromFile() {
	QString fileName = QFileDialog::getOpenFileName(this,
		"Load Population", "",
		"Text Files (*.txt);;All Files (*)");
}
void MainWindow::pauseSimulation(bool paused) {
	if (paused)
		loop_.stop();
	else
		loop_.start();
}
void MainWindow::carsNumberChanged() {
	qDebug() << "Cars number";
}