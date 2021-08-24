//===============================================
#include "GCircuitRC.h"
//===============================================
typedef struct _sGParams sGParams;
//===============================================
struct _sGParams {
    double R;
    double C;
    double Ve;
    double dVc;
    double Tmin;
    double Tmax;
    double Nmax;
};
//===============================================
GCircuitRC::GCircuitRC(QWidget* parent) : GElectronicsUi(parent) {
    init();

    sGParams* lParams = (sGParams*)m_params;

    QLabel* lRLabel = new QLabel;
    lRLabel->setText("R (\u03A9) :");
    QLineEdit* lREdit = new QLineEdit;
    m_REdit = lREdit;
    lREdit->setText(QString("%1").arg(lParams->R, 0, 'e', 0));
    lREdit->setStyleSheet("QLineEdit {max-width:50px;}");

    QLabel* lCLabel = new QLabel;
    lCLabel->setText("C (F) :");
    QLineEdit* lCEdit = new QLineEdit;
    m_CEdit = lCEdit;
    lCEdit->setText(QString("%1").arg(lParams->C));
    lCEdit->setStyleSheet("QLineEdit {max-width:50px;}");

    QLabel* lVeLabel = new QLabel;
    lVeLabel->setText("Ve (V) :");
    QLineEdit* lVeEdit = new QLineEdit;
    m_VeEdit = lVeEdit;
    lVeEdit->setText(QString("%1").arg(lParams->Ve));
    lVeEdit->setStyleSheet("QLineEdit {max-width:50px;}");

    QLabel* lTminLabel = new QLabel;
    lTminLabel->setText("Tmin (s) :");
    QLineEdit* lTminEdit = new QLineEdit;
    m_TminEdit = lTminEdit;
    lTminEdit->setText(QString("%1").arg(lParams->Tmin));
    lTminEdit->setStyleSheet("QLineEdit {max-width:50px;}");

    QLabel* lTmaxLabel = new QLabel;
    lTmaxLabel->setText("Tmax (s) :");
    QLineEdit* lTmaxEdit = new QLineEdit;
    m_TmaxEdit = lTmaxEdit;
    lTmaxEdit->setText(QString("%1").arg(lParams->Tmax, 0, 'e', 0));
    lTmaxEdit->setStyleSheet("QLineEdit {max-width:50px;}");

    QPushButton* lRunButton = new QPushButton;
    lRunButton->setText("Run");
    lRunButton->setStyleSheet("QPushButton {padding:5px;}");

    QHBoxLayout* lParamsLayout = new QHBoxLayout;
    lParamsLayout->addWidget(lRLabel);
    lParamsLayout->addWidget(lREdit);
    lParamsLayout->addWidget(lCLabel);
    lParamsLayout->addWidget(lCEdit);
    lParamsLayout->addWidget(lVeLabel);
    lParamsLayout->addWidget(lVeEdit);
    lParamsLayout->addWidget(lTminLabel);
    lParamsLayout->addWidget(lTminEdit);
    lParamsLayout->addWidget(lTmaxLabel);
    lParamsLayout->addWidget(lTmaxEdit);
    lParamsLayout->addStretch(1);
    lParamsLayout->addWidget(lRunButton);

    QCustomPlot* lPlot = new QCustomPlot;
    m_plot = lPlot;
    lPlot->addGraph();
    lPlot->addGraph();
    lPlot->addGraph();

    lPlot->graph(0)->setPen(QPen(QColor(0, 0, 180)));
    lPlot->graph(1)->setPen(QPen(QColor(0, 180, 0)));
    lPlot->graph(2)->setPen(QPen(QColor(180, 0, 0)));

    lPlot->graph(0)->setName("Vc");
    lPlot->graph(1)->setName("Vr");
    lPlot->graph(2)->setName("Ve");

    lPlot->legend->setVisible(true);
    lPlot->xAxis->setLabel("Temps (s)");
    lPlot->yAxis->setLabel("Tension (V)");

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lParamsLayout);
    lMainLayout->addWidget(lPlot, 1);

    setLayout(lMainLayout);

    compute();

    connect(lRunButton, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GCircuitRC::~GCircuitRC() {

}
//===============================================
void GCircuitRC::resize() {
    QFrame::resize(500,  300);
}
//===============================================
void GCircuitRC::init() {
    sGParams* lParams = new sGParams;
    m_params = lParams;
    lParams->R = 1e3;
    lParams->C = 1e-6;
    lParams->Ve = 5.0;
    lParams->Tmin = 0.0;
    lParams->Tmax = 5e-3;
    lParams->Nmax = 101;
}
//===============================================
void GCircuitRC::compute() {
    sGParams* lParams = (sGParams*)m_params;

    double R = lParams->R;
    double C = lParams->C;
    double Ve = lParams->Ve;

    gsl_odeiv2_system lSys = {onFunction, onJacobian, 1, lParams};

    gsl_odeiv2_driver* lOdeDriver = gsl_odeiv2_driver_alloc_y_new (
            &lSys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);

    double Tmin = lParams->Tmin;
    double Tmax = lParams->Tmax;
    double Nmax = lParams->Nmax;
    double dT = (Tmax - Tmin)/(Nmax - 1);
    double Ts = 0.0;
    double Yi[1] = {0.0};
    bool lOneOnly = true;
    double Vmin = 0.0;
    double Vmax = 0.0;

    m_Ts.clear();
    m_Vc.clear();
    m_Vr.clear();
    m_Ve.clear();

    for(double Ti = Tmin; Ti <= Tmax; Ti += dT) {
        int lStatus = gsl_odeiv2_driver_apply (lOdeDriver, &Ts, Ti, Yi);

        if (lStatus != GSL_SUCCESS) {
            printf ("[error] calcul incorrect : code erreur = %d\n", lStatus);
            break;
        }

        double Vc = Yi[0];
        double dVc = lParams->dVc;
        double I = C*dVc;
        double Vr = R*I;

        m_Ts.push_back(Ts);
        m_Vc.push_back(Vc);
        m_Vr.push_back(Vr);
        m_Ve.push_back(Ve);

        if(lOneOnly == true) {
            Vmin = Vc;
            Vmax = Vc;
            lOneOnly = false;
        }

        if(Vc < Vmin) {Vmin = Vc;}
        if(Vc > Vmax) {Vmax = Vc;}
        if(Vr < Vmin) {Vmin = Vr;}
        if(Vr > Vmax) {Vmax = Vr;}
        if(Ve < Vmin) {Vmin = Ve;}
        if(Ve > Vmax) {Vmax = Ve;}
    }

    m_plot->graph(0)->setData(m_Ts, m_Vc);
    m_plot->graph(1)->setData(m_Ts, m_Vr);
    m_plot->graph(2)->setData(m_Ts, m_Ve);

    m_plot->xAxis->setRange(Tmin, Tmax);
    m_plot->yAxis->setRange(Vmin, Vmax);

    m_plot->replot();
}
//===============================================
int GCircuitRC::onFunction (double t, const double y[], double f[], void *params) {
    sGParams* lParams = (sGParams*)params;
    double R = lParams->R;
    double C = lParams->C;
    double Ve = lParams->Ve;
    double Tau = R*C;
    f[0] = -(1/Tau)*y[0] + (1/Tau)*Ve;
    lParams->dVc = f[0];
    return GSL_SUCCESS;
}
//===============================================
int GCircuitRC::onJacobian (double t, const double y[], double *dfdy, double dfdt[], void *params) {
    sGParams* lParams = (sGParams*)params;
    double R = lParams->R;
    double C = lParams->C;
    double Tau = R*C;
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 1, 1);
    gsl_matrix* m = &dfdy_mat.matrix;
    gsl_matrix_set (m, 0, 0, -(1/Tau));
    dfdt[0] = 0.0;
    return GSL_SUCCESS;
}
//===============================================
void GCircuitRC::onEvent() {
    sGParams* lParams = (sGParams*)m_params;
    lParams->R = m_REdit->text().toDouble();
    lParams->C = m_CEdit->text().toDouble();
    lParams->Ve = m_VeEdit->text().toDouble();
    lParams->Tmin = m_TminEdit->text().toDouble();
    lParams->Tmax = m_TmaxEdit->text().toDouble();
    compute();
}
//===============================================
