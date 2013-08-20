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

    void importCurvesFromText( const QString& pFileName );

    void exportCurvesAsBinary( const QString& pFileName );

    void exportCurvesAsImage( const QString& pFileName );

    /**
     * Plotta bulunan egrileri Matlab (.m) dosya formatina uygun olarak
     * kayit eder.
     * @param pFileName kayit edilecek dosya ismi
     */
    void exportCurvesAsMatlab( const QString& pFileName );

    /**
     * Verilen satir ve sutundaki log variable ait bir egri var ise
     * true, yoksa false dondurur.
     * @param pLogVariable log variable
     * @param pRow log variable satiri
     * @param pColumn log variable sutunu
     * @return log variable ait egri varse true yoksa false getirir.
     */
    bool contains( LogVariable* pLogVariable, int pRow, int pCol );

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
