#include <sys/mman.h>
#include <QtGui/QApplication>
#include "zenom.h"

#include <QGtkStyle>

int main(int argc, char *argv[])
{
    mlockall ( MCL_CURRENT | MCL_FUTURE );

    QApplication a(argc, argv);
    a.setOrganizationName( "RobotLab" );
    a.setApplicationName( "Zenom" );
    a.setStyle(new QGtkStyle());

    Zenom w(argc, argv);
    w.show();

    return a.exec();
}
