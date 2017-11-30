#include <iostream>
#include <QMainWindow>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QMainWindow window;
	window.show();
	
	return a.exec();
}