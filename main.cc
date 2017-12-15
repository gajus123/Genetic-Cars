#include "Box2D/Box2D.h"
#include <QApplication>
#include "MainWindow.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow window;
	window.show();

	return app.exec();
}
