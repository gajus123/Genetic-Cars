/*!
 * @author Jakub Gajownik
 * @date 14.12.17
 *
 * \brief main initializes and starts app and main window
 */

#include "Box2D/Box2D.h"
#include <QApplication>
#include "MainWindow.h"
#include "include\Loop.h"
#include "include\ObjectsFactory.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	Physics::Loop loop;
	Physics::ObjectsFactory::init(loop);
	loop.run();
	
	MainWindow window;
	window.show();

	int result = app.exec();
	loop.stop();
	return result;
}
