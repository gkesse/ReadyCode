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
    void compute();
    static int onFunction (double t, const double y[], double f[], void *params);
    static int onJacobian (double t, const double y[], double *dfdy, double dfdt[], void *params);

private:
    QCustomPlot* m_plot;
    QVector<double> m_Ts;
    QVector<double> m_Vc;
    void* m_params;
};
//==============================================
#endif
//==============================================
