//===============================================
#include "GCircuitRC.h"
//===============================================
typedef struct _sGParams sGParams;
//===============================================
struct _sGParams {
	double R;
	double C;
	double Ve;
};
//===============================================
GCircuitRC::GCircuitRC(QWidget* parent) :
GElectronicsUi(parent) {
	QCustomPlot* lPlot = new QCustomPlot;
	m_plot = lPlot;

	compute();

	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addWidget(lPlot);

	setLayout(lMainLayout);
}
//===============================================
GCircuitRC::~GCircuitRC() {

}
//===============================================
void GCircuitRC::resize() {
	QFrame::resize(400,  300);
}
//===============================================
void GCircuitRC::compute() {
	sGParams* lParams = new sGParams;

	double R = 1e3;
	double C = 1e-6;
	double Ve = 5.0;

	double Tau = R*C;

	lParams->R = R;
	lParams->C = C;
	lParams->Ve = Ve;

	gsl_odeiv2_system lSys = {onFunction, onJacobian, 1, lParams};

	gsl_odeiv2_driver* lOdeDriver = gsl_odeiv2_driver_alloc_y_new (
			&lSys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);

	double Tmin = 0.0;
	double Tmax = 5*Tau;
	double Nmax = 101;
	double dT = (Tmax - Tmin)/(Nmax - 1);
	double Ts = 0.0;
	double Yi[1] = {0.0};
	bool lOneOnly = true;
	double Ymin = 0.0;
	double Ymax = 0.0;

	for(double Ti = Tmin; Ti <= Tmax; Ti += dT) {
		int lStatus = gsl_odeiv2_driver_apply (lOdeDriver, &Ts, Ti, Yi);

		if (lStatus != GSL_SUCCESS) {
			printf ("[error] calcul incorrect : code erreur = %d\n", lStatus);
			break;
		}

		m_Ts.push_back(Ts);
		m_Vc.push_back(Yi[0]);

		if(lOneOnly == true) {
			Ymin = Yi[0];
			Ymax = Yi[0];
			lOneOnly = false;
		}

		if(Yi[0] < Ymin) {Ymin = Yi[0];}
		if(Yi[0] > Ymax) {Ymax = Yi[0];}
	}

	m_plot->addGraph();
	m_plot->graph(0)->setData(m_Ts, m_Vc);
	m_plot->xAxis->setLabel("Temps (s)");
	m_plot->yAxis->setLabel("Tension (V)");
	m_plot->xAxis->setRange(Tmin, Tmax);
	m_plot->yAxis->setRange(Ymin, Ymax);
}
//===============================================
int GCircuitRC::onFunction (double t, const double y[], double f[], void *params) {
	sGParams* lParams = (sGParams*)params;
	double R = lParams->R;
	double C = lParams->C;
	double Ve = lParams->Ve;
	double Tau = R*C;
	f[0] = -(1/Tau)*y[0] + (1/Tau)*Ve;
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
