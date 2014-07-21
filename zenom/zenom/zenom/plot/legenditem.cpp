#include "legenditem.h"
#include "ui_legenditem.h"

LegendItem::LegendItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LegendItem)
{
    ui->setupUi(this);

    connect( ui->removeButton, SIGNAL(clicked()),
        SIGNAL(removeRequest()) );
    connect( ui->colorButton, SIGNAL(colorChanged(const QColor&)),
        SIGNAL(colorChanged(const QColor&)) );

    ui->lineSizeCombo;
}

LegendItem::~LegendItem()
{
    delete ui;
}

void LegendItem::setName( const QString& pName )
{
    ui->curveName->setText( pName );
}

void LegendItem::setColor( const QColor& pColor )
{
    ui->colorButton->setColor( pColor );
}
