//===============================================
#ifndef _GCircuitRC_
#define _GCircuitRC_
//===============================================
#include "GElectronicsUi.h"
//===============================================
class GCircuitRC : public GElectronicsUi {
    Q_OBJECT
    
public:
    GCircuitRC(QWidget* parent = 0);
    virtual ~GCircuitRC();
    void resize();

private:
    void compute();

private:
    QCustomPlot* m_plot;
    QVector<double> m_xData;
    QVector<double> m_yData;
};
//==============================================
#endif
//==============================================
