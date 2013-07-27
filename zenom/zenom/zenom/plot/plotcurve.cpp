#include "plotcurve.h"

#include "legenditem.h"
#include "plot.h"

#include <qwt_series_data.h>

/*
 *  CurveData
 */
CurveData::CurveData()
    : mLastHeapSize(0)
{

}

void CurveData::updateBoundingRect()
{
    if ( mLogVariableItem.isValid() && mLastHeapSize != mLogVariableItem.size() )
    {
        mLastHeapSize = mLogVariableItem.size();
        d_boundingRect = qwtBoundingRect( *this );   // TODO
    }
}

void CurveData::setLogVariableItem(const LogVariableItem& pItem )
{
    mLogVariableItem = pItem;
}

LogVariableItem CurveData::logVariableItem()
{
    return mLogVariableItem;
}

void CurveData::saveSettings(QSettings &pSettings)
{
    mLogVariableItem.saveSettings(pSettings);
}

void CurveData::loadSettings(QSettings &pSettings)
{
    mLogVariableItem.loadSettings(pSettings);
}


/*
 *  PlotCurve
 */
PlotCurve::PlotCurve(const QString& pTitle) :
    QwtPlotCurve(pTitle)
{
    setRenderHint( RenderAntialiased);
    mCurveData = new CurveData;
    setData(mCurveData);
}

void PlotCurve::setLogVariableItem(const LogVariableItem& pItem )
{
    mCurveData->setLogVariableItem( pItem );
}

LogVariableItem PlotCurve::logVariableItem()
{
    return mCurveData->logVariableItem();
}

void PlotCurve::saveSettings(QSettings &pSettings)
{
    pSettings.setValue("title", title().text());
    pSettings.setValue("ColorR", pen().color().red());
    pSettings.setValue("ColorG", pen().color().green());
    pSettings.setValue("ColorB", pen().color().blue());
    mCurveData->saveSettings(pSettings);
}

void PlotCurve::loadSettings(QSettings &pSettings)
{
    setTitle( pSettings.value("title").toString() );
    QColor curveColor ( pSettings.value("ColorR").toInt(),
                        pSettings.value("ColorG").toInt(),
                        pSettings.value("ColorB").toInt() );
    setPen(QPen(curveColor));
    mCurveData->loadSettings(pSettings);
}

void PlotCurve::tick()
{
    mCurveData->updateBoundingRect();
}

QWidget* PlotCurve::legendItem() const
{
    LegendItem* legendItem = new LegendItem();
    legendItem->setName( title().text() );
    legendItem->setColor( pen().color() );

    // Do not delete object, during its event handler
    QObject::connect( legendItem, SIGNAL( removeRequest() ),
        (Plot*) plot(), SLOT( legendRemoveRequest() ), Qt::QueuedConnection );

    QObject::connect( legendItem, SIGNAL( colorChanged(const QColor&) ),
        (Plot*) plot(), SLOT( legendColorChanged(const QColor&) ) );

    return legendItem;
}
