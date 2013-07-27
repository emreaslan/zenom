#ifndef PLOT_H
#define PLOT_H


#include <QString>
#include <QSettings>
#include <qwt_plot.h>
#include <qwt_plot_panner.h>
#include "widget/logvariableitem.h"
#include "plotcurve.h"
#include "curvecolorgenerator.h"


class Plot : public QwtPlot
{
    Q_OBJECT
public:
    Plot(QWidget* pParent = NULL);

    virtual ~Plot();

    virtual void saveSettings( QSettings& pSettings );

    virtual void loadSettings( QSettings& pSettings );

    void attactLogVariableItems( const QList<LogVariableItem>& pLogVariableItems );

    void tick();

    double timeInterval();

    void setTimeInterval( double pInterval );

    bool autoscale();

    void setAutoscale( bool pOn );

signals:
    void autoscaleOff();

protected slots:
    void legendColorChanged( const QColor& pColor );

    void legendRemoveRequest();

    void zoommed_or_panned();

private:
    void setAutoscaleAndInterval( bool pOn, double pMin, double pMax );

    QVector<PlotCurve*> mCurveVec;
    CurveColorGenerator mColorGenerator;
    QwtInterval d_interval;
    bool mAutoscale;
};

#endif // PLOT_H
