#include "plot.h"

#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include "plotmagnifier.h"


Plot::Plot(QWidget* pParent): QwtPlot(pParent)
{
    setAxisTitle( QwtPlot::xBottom, "Time [s]" );
    setCanvasBackground( Qt::white );
    insertLegend( new QwtLegend, QwtPlot::RightLegend );

    // panning with the left mouse button
    QwtPlotPanner* plotPanner = new QwtPlotPanner( canvas() );
    connect( plotPanner, SIGNAL(panned(int,int)), this, SLOT(zoommed_or_panned()) );

    // zoom in/out with the wheel
    PlotMagnifier* plotMagnifier = new PlotMagnifier( canvas() );
    connect( plotMagnifier, SIGNAL(zoomed()), this, SLOT(zoommed_or_panned()) );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen( QPen( Qt::gray, 0.0, Qt::DotLine ) );
    grid->attach( this );

    QwtPlotMarker *d_origin = new QwtPlotMarker();
    d_origin->setLineStyle( QwtPlotMarker::Cross );
    d_origin->setValue( 0.0, 0.0 );
    d_origin->setLinePen( QPen( Qt::gray, 0.0, Qt::DashLine ) );
    d_origin->attach( this );

    setAutoscaleAndInterval( true, 0, 10 );
}

Plot::~Plot()
{

}

void Plot::saveSettings( QSettings& pSettings )
{
    pSettings.setValue("timeInterval", timeInterval());
    pSettings.setValue("curveCount", mCurveVec.size());
    for (int i = 0; i < mCurveVec.size(); ++i)
    {
        pSettings.beginGroup( QString("curve") + QString::number(i) );
        mCurveVec[i]->saveSettings(pSettings);
        pSettings.endGroup();
    }
}

void Plot::loadSettings( QSettings& pSettings )
{
    mColorGenerator.reset();
    setTimeInterval( pSettings.value("timeInterval", 10).toInt() );
    int curveCount = pSettings.value("curveCount").toInt();
    for (int i = 0; i < curveCount; ++i)
    {
        pSettings.beginGroup( QString("curve") + QString::number(i) );
        PlotCurve* newCurve = new PlotCurve( );
        newCurve->loadSettings(pSettings);
        pSettings.endGroup();
        newCurve->attach( this );
        mCurveVec.push_back(newCurve);
        mColorGenerator.increaseIndex();
    }
}

void Plot::attactLogVariableItems( const QList<LogVariableItem>& pLogVariableItems )
{
    for ( int i = 0; i < pLogVariableItems.size(); ++i )
    {
        QString name = QString("%1[%2][%3]").arg(QString::fromStdString(pLogVariableItems[i].logVariable()->name()))
                .arg( pLogVariableItems[i].row() )
                .arg( pLogVariableItems[i].column() );

        PlotCurve* newCurve = new PlotCurve( name );
        newCurve->setLogVariableItem( pLogVariableItems[i]);
        newCurve->setPen( QPen( mColorGenerator.generateColor() ));
        newCurve->attach( this );
        mCurveVec.push_back(newCurve);
    }
}

void Plot::tick()
{
    double maxTime = -1;
    for (int i = 0 ; i < mCurveVec.size(); ++i)
    {
        mCurveVec[i]->tick();
        maxTime = qMax( maxTime, mCurveVec[i]->data()->boundingRect().right() );
    }

    // Increment interval
    if ( maxTime > d_interval.maxValue() )
    {
        setAutoscaleAndInterval( autoscale(), d_interval.maxValue(), d_interval.maxValue() + timeInterval() );
    }

    // rescale when simulation start
    if ( maxTime < d_interval.minValue() )
    {
        setAutoscaleAndInterval( autoscale(), 0, timeInterval() );
    }

    replot();
}

void Plot::legendColorChanged( const QColor& pColor )
{
    if ( legend() && sender()->isWidgetType() )
    {
        PlotCurve* curve = (PlotCurve*) legend()->find( ( QWidget * )sender() );
        curve->setPen( QPen( pColor ) );
        replot();
    }
}

void Plot::legendRemoveRequest()
{
    if ( legend() && sender()->isWidgetType() )
    {
        PlotCurve* curve = (PlotCurve*) legend()->find( ( QWidget * )sender() );

        for (int i = 0; i < mCurveVec.size(); ++i)
        {
            if ( mCurveVec[i] == curve )
            {
                mCurveVec.remove( i );
                break;
            }
        }

        delete curve;
        replot();
        updateLayout();
    }
}

double Plot::timeInterval()
{
    return d_interval.width();
}

void Plot::setTimeInterval(double pInterval)
{
    setAutoscaleAndInterval( autoscale(), d_interval.minValue(), d_interval.minValue() + pInterval );
}

bool Plot::autoscale()
{
    return mAutoscale;
}

void Plot::setAutoscale( bool pOn )
{
    setAutoscaleAndInterval( pOn, d_interval.minValue(), d_interval.maxValue() );
}

void Plot::zoommed_or_panned()
{
    setAutoscale(false);
    emit autoscaleOff();
}

void Plot::setAutoscaleAndInterval( bool pOn, double pMin, double pMax )
{
    mAutoscale = pOn;

    d_interval.setMinValue( pMin );
    d_interval.setMaxValue( pMax );

    if ( pOn )
    {
        setAxisAutoScale( QwtPlot::yLeft );
        setAxisScale(QwtPlot::xBottom, d_interval.minValue(), d_interval.maxValue());
    }
}
