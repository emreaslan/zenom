#include "linesizecombobox.h"
#include <QIcon>

LineSizeComboBox::LineSizeComboBox(QWidget *parent) :
    QComboBox(parent)
{
    fillComboBox();
    connect(this, SIGNAL( currentIndexChanged(int) ), SLOT( on_SelectedSizeChanged(int) ));
}

void LineSizeComboBox::on_SelectedSizeChanged(int)
{

}

void LineSizeComboBox::fillComboBox()
{

    for (int i = 0; i < 10; ++i)
    {
        QSize pixmapSize(10, i+1);
        QPixmap pixmap(pixmapSize);
        pixmap.fill(Qt::black);
        QIcon *icon = new QIcon(pixmap);

        this->addItem(*icon, "");
    }

}
