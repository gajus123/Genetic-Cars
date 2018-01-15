/*!
 * @authors Jakub Gajownik, Rafał Galczak
 * @date 14.12.17
 *
 */
#include "MainWindow.h"
#include "include/GroundGenerator.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
	QMainWindow(parent, flags),
	mutation_size_label_("Prawdopodobieństwo mutacji: "),
	elite_specimen_number_label_("Ilość osobników elitarnych: "),
	load_button_("Wczytaj"),
	save_button_("Zapisz"),
	reset_button_("Resetuj"),
	pause_button_("Pauza"),
	cars_count_label_("Ilość pojazdów: "),
	simulation_(),
	simulation_view_(simulation_) {

	setWindowTitle("Genetic Cars"); 
	
	//Create container for left and right side
	QWidget* central_widget;
	QHBoxLayout* central_layout;
	std::tie(central_widget, central_layout) = createLayout<QWidget, QHBoxLayout>();
	setCentralWidget(central_widget);

	//Create left side container 
	QWidget* content;
	QVBoxLayout* content_layout;
	std::tie(content, content_layout) = createLayout<QWidget, QVBoxLayout>(central_layout);

	//Create size policy for left side
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setVerticalStretch(3);

	//Set simulation view to expand and height to 3/5
	simulation_view_.setSizePolicy(sizePolicy);
	content_layout->addWidget(&simulation_view_);

	//Set statistic view to expand and height to 2/5
	sizePolicy.setVerticalStretch(2);
	statistic_view_.setSizePolicy(sizePolicy);
	content_layout->addWidget(&statistic_view_);


	//Create right side container
	QWidget* sidebar_container;
	QVBoxLayout* sidebar_layout;
	std::tie(sidebar_container, sidebar_layout) = createLayout<QWidget, QVBoxLayout>(central_layout);
	
	central_layout->setAlignment(sidebar_container, Qt::AlignTop);
	sidebar_container->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	sidebar_layout->addWidget(createSimulationWidgets());
	sidebar_layout->addWidget(createFileWidgets());
	sidebar_layout->addWidget(createAlgorithmWidgets());


	connect(&elite_specimen_number_edit_, SIGNAL(editingFinished()), this, SLOT(mutationRateChanged()));
	connect(&mutation_size_edit_, SIGNAL(editingFinished()), this, SLOT(mutationSizeChanged()));
	connect(&load_button_, SIGNAL(clicked()), this, SLOT(loadFromFile()));
	connect(&save_button_, SIGNAL(clicked()), this, SLOT(saveToFile()));
	connect(&reset_button_, SIGNAL(clicked()), this, SLOT(resetSimulation()));
	connect(&pause_button_, SIGNAL(toggled(bool)), this, SLOT(pauseSimulation(bool)));
	connect(&cars_count_edit_, SIGNAL(editingFinished()), this, SLOT(carsNumberChanged()));
	connect(&simulation_speed_chooser_, SIGNAL(currentIndexChanged(int)), this, SLOT(speedChanged()));

	connect(&simulation_, SIGNAL(roundEnd(std::vector<float>)), &statistics_, SLOT(calculateStatistics(std::vector<float>)));
	connect(&statistics_, SIGNAL(newValues(float, float, float, float)), &statistic_view_, SLOT(addData(float, float, float, float)));

	connect(&simulation_, SIGNAL(roundEnd(std::vector<float>)), &population_, SLOT(nextPopulation(std::vector<float>)));
	connect(&population_, SIGNAL(newVehiclesGenerated(std::vector<Objects::Vehicle>)), &simulation_, SLOT(newRound(std::vector<Objects::Vehicle>)));

	Physics::ObjectsFactory::init(loop_);

	simulation_.newGround();
	population_.inflateRandom();
}
QWidget* MainWindow::createSimulationWidgets() {
	//Create container for Simulation manipulation widgets
	QGroupBox* groupBox;
	QVBoxLayout* layout;
	std::tie(groupBox, layout) = createLayout<QGroupBox, QVBoxLayout>();
	groupBox->setTitle("Symulacja");

	//Add widgets to created container
	layout->addWidget(&reset_button_);
	layout->addWidget(&pause_button_);

	//Create container for Speed manipulation widget
	QGroupBox* speedContainer;
	QHBoxLayout* speedLayout;
	std::tie(speedContainer, speedLayout) = createLayout<QGroupBox, QHBoxLayout>(layout);
	speedContainer->setTitle("Prędkość symulacji");

	speedLayout->addWidget(&simulation_speed_chooser_);

	//Create container for Cars number manipulation widgets
	QHBoxLayout* carsLayout;
	std::tie(std::ignore, carsLayout) = createLayout<QWidget, QHBoxLayout>(layout);

	//Add widgets to created container
	carsLayout->addWidget(&cars_count_label_);
	carsLayout->addWidget(&cars_count_edit_);

	//Set widgets properties
	pause_button_.setCheckable(true);
	cars_count_edit_.setText(QString::number(population_.getNextGenerationSize()));
	mutation_size_edit_.setText(QString().setNum(population_.getMutationRate()));
	elite_specimen_number_edit_.setText(QString::number(population_.getEliteSpecimen()));

	initializeSpeedWidget();

	return groupBox;
}
QWidget* MainWindow::createFileWidgets() {
	//Create group box for File manipulation widgets
	QGroupBox* groupBox;
	QHBoxLayout* layout;
	std::tie(groupBox, layout) = createLayout<QGroupBox, QHBoxLayout>();
	groupBox->setTitle("Zapis/odczyt");

	//Add widgets to created group box
	layout->addWidget(&load_button_);
	layout->addWidget(&save_button_);

	return groupBox;
}
QWidget* MainWindow::createAlgorithmWidgets() {
	//Create group box for Algorithm settings
	QGroupBox* groupBox;
	QHBoxLayout* layout;
	std::tie(groupBox, layout) = createLayout<QGroupBox, QHBoxLayout>();
	groupBox->setTitle("Parametry algorytmu genetycznego");

	//Create column for Mutation settings labels
	QVBoxLayout* labelsLayout;
	std::tie(std::ignore, labelsLayout) = createLayout<QWidget, QVBoxLayout>(layout);

	labelsLayout->addWidget(&mutation_size_label_);
	labelsLayout->addWidget(&elite_specimen_number_label_);

	//Create column for Mutation settings inputs
	QVBoxLayout* editsLayout;
	std::tie(std::ignore, editsLayout) = createLayout<QWidget, QVBoxLayout>(layout);

	editsLayout->addWidget(&mutation_size_edit_);
	editsLayout->addWidget(&elite_specimen_number_edit_);

	return groupBox;
}
void MainWindow::initializeSpeedWidget() {
	simulation_speed_chooser_.addItem("25%", QVariant(1.0f / 240.0f));
	simulation_speed_chooser_.addItem("50%", QVariant(1.0f / 120.0f));
	simulation_speed_chooser_.addItem("75%", QVariant(1.0f / 80.0f));
	simulation_speed_chooser_.addItem("100%", QVariant(1.0f/ 60.0f));
	simulation_speed_chooser_.addItem("150%", QVariant(1.0f / 40.0f));
	simulation_speed_chooser_.addItem("200%", QVariant(1.0f / 30.0f));
	simulation_speed_chooser_.addItem("300%", QVariant(1.0f / 20.0f));
	simulation_speed_chooser_.addItem("400%", QVariant(1.0f / 15.0f));
	simulation_speed_chooser_.addItem("500%", QVariant(1.0f / 12.0f));
	simulation_speed_chooser_.setCurrentIndex(3);
}
void MainWindow::mutationRateChanged() {
	QString new_text = elite_specimen_number_edit_.text();
	bool is_int;
	std::size_t elite_specimen = new_text.toInt(&is_int);
	if (is_int)
		population_.setEliteSpecimen(elite_specimen);
	elite_specimen_number_edit_.setText(QString::number(population_.getEliteSpecimen()));
}
void MainWindow::mutationSizeChanged() {
	bool is_float;
	float mutation_size = mutation_size_edit_.text().toFloat(&is_float);
	if (is_float)
		population_.setMutationRate(mutation_size);
	mutation_size_edit_.setText(QString().setNum(population_.getMutationRate()));
}
void MainWindow::saveToFile() {
	if (!pause_button_.isChecked())
		pauseSimulation();

	QString filename = QFileDialog::getSaveFileName(this,
		"Save Population", "",
		"Text Files (*.txt);;All Files (*)");

	if (!filename.isEmpty())
		population_.saveToFile(filename.toStdString());

	if (!pause_button_.isChecked())
		resumeSimulation();
}
void MainWindow::loadFromFile() {
	if (!pause_button_.isChecked())
		pauseSimulation();

	QString filename = QFileDialog::getOpenFileName(this,
		"Load Population", "",
		"Text Files (*.txt);;All Files (*)");

	if (!filename.isEmpty())
		population_.loadFromFile(filename.toStdString());

	if (!pause_button_.isChecked())
		resumeSimulation();
}
void MainWindow::pauseSimulation(bool paused) {
	if (paused)
		pauseSimulation();
	else
		resumeSimulation();
}
void MainWindow::carsNumberChanged() {
	QString new_text = cars_count_edit_.text();
	bool is_int;
	std::size_t cars_number = new_text.toInt(&is_int);
	if (is_int)
		population_.setNextGenerationSize(cars_number);
	cars_count_edit_.setText(QString::number(population_.getNextGenerationSize()));
}
void MainWindow::resetSimulation() {
	statistic_view_.reset();
	simulation_.reset();
	population_.reset();
}
void MainWindow::speedChanged() {
	loop_.setTimeStep(simulation_speed_chooser_.currentData().toFloat());
}
void MainWindow::pauseSimulation() {
	loop_.stop();
	simulation_.stop();
}
void MainWindow::resumeSimulation() {
	loop_.start();
	simulation_.start();
}

template<class WidgetType, class LayoutType>
std::tuple<WidgetType*, LayoutType*> MainWindow::createLayout(QLayout* parent_layout) {
	WidgetType* widget = new WidgetType();
	LayoutType* layout = new LayoutType(widget);

	if (parent_layout != Q_NULLPTR)
		parent_layout->addWidget(widget);
	return std::make_tuple(widget, layout);
}