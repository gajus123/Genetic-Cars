/*!
 * @authors Jakub Gajownik, Rafał Galczak
 * @date 14.12.17
 *
 */
#include <MainWindow.h>
#include <GroundGenerator.h>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
	QMainWindow(parent, flags),
	simulation_(),
	simulation_view_(simulation_),
    ui_(new Ui::MainWindow),
    pause_action_(QKeySequence(Qt::CTRL + Qt::Key_P), this) {

    ui_->setupUi(this);

    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setVerticalStretch(3);
    simulation_view_.setSizePolicy(sizePolicy);
    ui_->verticalLayout_3->addWidget(&simulation_view_);
    sizePolicy.setVerticalStretch(2);
    statistic_view_.setSizePolicy(sizePolicy);
    ui_->verticalLayout_3->addWidget(&statistic_view_);

    connect(&pause_action_, SIGNAL(activated()), ui_->pause_button, SLOT(click()));

    connect(ui_->elite_specimen_number_edit, SIGNAL(editingFinished()), this, SLOT(eliteSpecimenNumberChanged()));
    connect(ui_->mutation_size_edit, SIGNAL(editingFinished()), this, SLOT(mutationSizeChanged()));
    connect(ui_->load_button, SIGNAL(clicked()), this, SLOT(loadFromFile()));
    connect(ui_->save_button, SIGNAL(clicked()), this, SLOT(saveToFile()));
    connect(ui_->reset_button, SIGNAL(clicked()), this, SLOT(resetSimulation()));
    connect(ui_->pause_button, SIGNAL(toggled(bool)), this, SLOT(pauseSimulation(bool)));
    connect(ui_->cars_count_edit, SIGNAL(editingFinished()), this, SLOT(carsNumberChanged()));
    connect(ui_->simulation_speed_chooser, SIGNAL(currentIndexChanged(int)), this, SLOT(speedChanged()));


    connect(&simulation_, SIGNAL(roundEnd(std::vector<float>)), &statistics_, SLOT(calculateStatistics(std::vector<float>)));
    connect(&statistics_, SIGNAL(newValues(float, float, float, float)), &statistic_view_, SLOT(addData(float, float, float, float)));

    connect(&simulation_, SIGNAL(roundEnd(std::vector<float>)), &population_, SLOT(nextPopulation(std::vector<float>)));
    connect(&population_, SIGNAL(newVehiclesGenerated(std::vector<Objects::Vehicle>)), &simulation_, SLOT(newRound(std::vector<Objects::Vehicle>)));

    connect(&loop_, SIGNAL(step(unsigned int)), &simulation_, SLOT(step(unsigned int)));

    Physics::ObjectsFactory::init(simulation_.getWorld().getWorld());

    simulation_.newGround();
    population_.generateVehicles();

    initializeSpeedWidget();

    ui_->cars_count_edit->setText(QString::number(population_.nextGenerationSize()));
    ui_->mutation_size_edit->setText(QString::number(population_.mutationRate()));
    ui_->elite_specimen_number_edit->setText(QString::number(population_.eliteSpecimen()));
}
void MainWindow::initializeSpeedWidget() {
	ui_->simulation_speed_chooser->addItem("25%", QVariant(0.25f));
	ui_->simulation_speed_chooser->addItem("50%", QVariant(0.5f));
	ui_->simulation_speed_chooser->addItem("75%", QVariant(0.75f));
	ui_->simulation_speed_chooser->addItem("100%", QVariant(1.0f));
	ui_->simulation_speed_chooser->addItem("150%", QVariant(1.5f));
	ui_->simulation_speed_chooser->addItem("200%", QVariant(2.0f));
	ui_->simulation_speed_chooser->addItem("300%", QVariant(3.0f));
	ui_->simulation_speed_chooser->addItem("400%", QVariant(4.0f));
	ui_->simulation_speed_chooser->addItem("500%", QVariant(5.0f));
	ui_->simulation_speed_chooser->setCurrentIndex(3);
}
void MainWindow::eliteSpecimenNumberChanged() {
	QString new_text = ui_->elite_specimen_number_edit->text();
	bool is_int;
	std::size_t elite_specimen = new_text.toInt(&is_int);
	if (is_int)
		population_.setEliteSpecimen(elite_specimen);
	ui_->elite_specimen_number_edit->setText(QString::number(population_.eliteSpecimen()));
}
void MainWindow::mutationSizeChanged() {
	bool is_float;
	float mutation_size = ui_->mutation_size_edit->text().toFloat(&is_float);
	if (is_float)
		population_.setMutationRate(mutation_size);
	ui_->mutation_size_edit->setText(QString().setNum(population_.mutationRate()));
}
void MainWindow::saveToFile() {
	if (!ui_->pause_button->isChecked())
		pauseSimulation();

    QFileDialog file_dialog{this, "Load Population", "", "Text Files (*.txt);;AllFiles (*)"};
    file_dialog.setAcceptMode(QFileDialog::AcceptSave);
    file_dialog.setFileMode(QFileDialog::AnyFile);
    file_dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    if(QDialog::Accepted != file_dialog.exec()) {
        if (!ui_->pause_button->isChecked())
            resumeSimulation();
        return;
    }
    QString filename = file_dialog.selectedFiles().at(0);

	if (!filename.isEmpty())
		population_.saveToFile(filename.toStdString());

	if (!ui_->pause_button->isChecked())
		resumeSimulation();
}
void MainWindow::loadFromFile() {
	if (!ui_->pause_button->isChecked())
		pauseSimulation();

	QFileDialog file_dialog{this, "Load Population", "", "Text Files (*.txt);;AllFiles (*)"};
	file_dialog.setAcceptMode(QFileDialog::AcceptOpen);
	file_dialog.setFileMode(QFileDialog::ExistingFile);
	file_dialog.setOption(QFileDialog::DontUseNativeDialog, true);
	if(QDialog::Accepted != file_dialog.exec()) {
        if (!ui_->pause_button->isChecked())
            resumeSimulation();
	    return;
	}
	QString filename = file_dialog.selectedFiles().at(0);

	if (!filename.isEmpty())
		population_.loadFromFile(filename.toStdString());

	if (!ui_->pause_button->isChecked())
		resumeSimulation();
}
void MainWindow::pauseSimulation(bool paused) {
	if (paused)
		pauseSimulation();
	else
		resumeSimulation();
}
void MainWindow::carsNumberChanged() {
	QString new_text = ui_->cars_count_edit->text();
	bool is_int;
	std::size_t cars_number = new_text.toInt(&is_int);
	if (is_int)
		population_.setNextGenerationSize(cars_number);
	ui_->cars_count_edit->setText(QString::number(population_.nextGenerationSize()));
	ui_->elite_specimen_number_edit->setText(QString::number(population_.eliteSpecimen()));
}
void MainWindow::resetSimulation() {
	statistic_view_.reset();
	simulation_.reset();
	population_.reset();
}
void MainWindow::speedChanged() {
	float time_speed = ui_->simulation_speed_chooser->currentData().toFloat();
	loop_.setTimeSpeed(time_speed);
}
void MainWindow::pauseSimulation() {
	loop_.stop();
}
void MainWindow::resumeSimulation() {
	loop_.start();
}