/*!
 * @author Jakub Gajownik
 * @date 14.12.17
 *
 * \brief main initializes and starts app and main window
 */

#include "Box2D/Box2D.h"
#include <QApplication>
#include "include/MainWindow.h"
#include "include/ObjectsFactory.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	MainWindow window;
	window.show();

	return app.exec();
}