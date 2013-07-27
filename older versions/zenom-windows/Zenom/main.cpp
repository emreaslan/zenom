#include "zenom.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Zenom w;
	w.show();
	return a.exec();
}
