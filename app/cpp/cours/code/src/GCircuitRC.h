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
    void init();
    void compute();
    static int onFunction (double t, const double y[], double f[], void *params);
    static int onJacobian (double t, const double y[], double *dfdy, double dfdt[], void *params);

public slots:
    void onEvent();

private:
    QCustomPlot* m_plot;
    QLineEdit* m_REdit;
    QLineEdit* m_CEdit;
    QLineEdit* m_VeEdit;
    QLineEdit* m_TminEdit;
    QLineEdit* m_TmaxEdit;
    QVector<double> m_Ts;
    QVector<double> m_Vc;
    QVector<double> m_Vr;
    QVector<double> m_Ve;
    void* m_params;
};
//==============================================
#endif
//==============================================
