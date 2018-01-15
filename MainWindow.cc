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
	mutation_rate_label_("Współczynnik mutacji: "),
	load_button_("Wczytaj"),
	save_button_("Zapisz"),
	reset_button_("Resetuj"),
	pause_button_("Pauza"),
	cars_count_label_("Ilość pojazdów: "),
	simulation_(),
	simulation_view_(simulation_) {

	setWindowTitle("Genetic Cars"); 
	
	//Create container for left and right side
	QWidget* centralWidget;
	QHBoxLayout* centralLayout;
	std::tie(centralWidget, centralLayout) = createLayout<QWidget, QHBoxLayout>();
	setCentralWidget(centralWidget);

	//Create left side container 
	QWidget* content;
	QVBoxLayout* contentLayout;
	std::tie(content, contentLayout) = createLayout<QWidget, QVBoxLayout>(centralLayout);

	//Create size policy for left side
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setVerticalStretch(3);

	//Set simulation view to expand and height to 3/5
	simulation_view_.setSizePolicy(sizePolicy);
	contentLayout->addWidget(&simulation_view_);

	//Set statistic view to expand and height to 2/5
	sizePolicy.setVerticalStretch(2);
	statistic_view_.setSizePolicy(sizePolicy);
	contentLayout->addWidget(&statistic_view_);


	//Create right side container
	QWidget* sidebarContainer;
	QVBoxLayout* sidebarLayout;
	std::tie(sidebarContainer, sidebarLayout) = createLayout<QWidget, QVBoxLayout>(centralLayout);
	
	centralLayout->setAlignment(sidebarContainer, Qt::AlignTop);
	sidebarContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	sidebarLayout->addWidget(setupSimulationInterface());
	sidebarLayout->addWidget(setupFileInterface());
	sidebarLayout->addWidget(setupAlgorithmInterface());


	connect(&mutation_rate_edit_, SIGNAL(editingFinished()), this, SLOT(mutationRateChanged()));
	connect(&mutation_size_edit_, SIGNAL(editingFinished()), this, SLOT(mutationSizeChanged()));
	connect(&load_button_, SIGNAL(clicked()), this, SLOT(loadFromFile()));
	connect(&save_button_, SIGNAL(clicked()), this, SLOT(saveToFile()));
	connect(&reset_button_, SIGNAL(clicked()), &simulation_, SLOT(reset()));
	connect(&pause_button_, SIGNAL(toggled(bool)), this, SLOT(pauseSimulation(bool)));
	connect(&cars_count_edit_, SIGNAL(editingFinished()), this, SLOT(carsNumberChanged()));

	Physics::ObjectsFactory::init(loop_);

	simulation_.newGround();
	simulation_.newVehicles();

	/*statistic_view_.addData(1.0, 0.5, 0.2, 0.3);
	statistic_view_.addData(2.0, 1.0, 0.6, 0.65);
	statistic_view_.reset();
	statistic_view_.addData(0.5, 0.1, 0.3, 0.2);*/
}
QWidget* MainWindow::setupSimulationInterface() {
	//Create container for Simulation manipulation widgets
	QGroupBox* groupBox;
	QVBoxLayout* layout;
	std::tie(groupBox, layout) = createLayout<QGroupBox, QVBoxLayout>();
	groupBox->setTitle("Symulacja");

	//Add widgets to created container
	layout->addWidget(&reset_button_);
	layout->addWidget(&pause_button_);

	//Create container for Speed manipulation widgets
	QGroupBox* speedContainer;
	QHBoxLayout* speedLayout;
	std::tie(speedContainer, speedLayout) = createLayout<QGroupBox, QHBoxLayout>(layout);
	speedContainer->setTitle("Prędkość symulacji");

	//Add widgets to created container
	speedLayout->addWidget(&speed_decrease_button_);
	speedLayout->addWidget(&speed_label_);
	speedLayout->addWidget(&speed_increase_button_);

	//Create container for Cars number manipulation widgets
	QHBoxLayout* carsLayout;
	std::tie(std::ignore, carsLayout) = createLayout<QWidget, QHBoxLayout>(layout);

	//Add widgets to created container
	carsLayout->addWidget(&cars_count_label_);
	carsLayout->addWidget(&cars_count_edit_);

	//Set widgets properties
	pause_button_.setCheckable(true);
	speed_decrease_button_.setText("-");
	speed_increase_button_.setText("+");
	speed_label_.setText("10");
	speed_label_.setAlignment(Qt::AlignCenter);
	cars_count_edit_.setText(QString::number(simulation_.getPopulationSize()));

	return groupBox;
}
QWidget* MainWindow::setupFileInterface() {
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
QWidget* MainWindow::setupAlgorithmInterface() {
	//Create group box for Algorithm settings
	QGroupBox* groupBox;
	QHBoxLayout* layout;
	std::tie(groupBox, layout) = createLayout<QGroupBox, QHBoxLayout>();
	groupBox->setTitle("Parametry algorytmu genetycznego");

	//Create column for Mutation settings labels
	QVBoxLayout* labelsLayout;
	std::tie(std::ignore, labelsLayout) = createLayout<QWidget, QVBoxLayout>(layout);

	labelsLayout->addWidget(&mutation_size_label_);
	labelsLayout->addWidget(&mutation_rate_label_);

	//Create column for Mutation settings inputs
	QVBoxLayout* editsLayout;
	std::tie(std::ignore, editsLayout) = createLayout<QWidget, QVBoxLayout>(layout);

	editsLayout->addWidget(&mutation_size_edit_);
	editsLayout->addWidget(&mutation_rate_edit_);

	return groupBox;
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
	QString newText = cars_count_edit_.text();
	bool ok;
	std::size_t newCarNumber = newText.toInt(&ok);
	if (ok)
	{
		simulation_.setPopulationSize(newCarNumber);
	}
	cars_count_edit_.setText(QString::number(simulation_.getPopulationSize()));
}

template<class WidgetType, class LayoutType>
std::tuple<WidgetType*, LayoutType*> MainWindow::createLayout(QLayout* parentLayout) {
	WidgetType* widget = new WidgetType();
	LayoutType* layout = new LayoutType(widget);

	if (parentLayout != Q_NULLPTR)
		parentLayout->addWidget(widget);
	return std::make_tuple(widget, layout);
}