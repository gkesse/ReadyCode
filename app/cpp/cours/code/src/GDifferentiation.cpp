//===============================================
#include "GDifferentiation.h"
//===============================================
GDifferentiation::GDifferentiation(QWidget* parent) : GGslUi(parent) {
	gsl_function F;
	F.function = &onFunction;
	F.params = 0;

	QVector<double> Xt, Yt, dYt;

	double Xmin = -1.0;
	double Xmax = 1.0;
	int Nmax = 101;
	double dX = (Xmax - Xmin)/(Nmax - 1);
	double Ymin, Ymax;
	bool lOneOnly = true;

	for(double Xi = Xmin; Xi <= Xmax; Xi += dX) {
		double dYi, dError;
		double Yi = onFunction(Xi, 0);
		Xt.push_back(Xi);
		Yt.push_back(Yi);
		gsl_deriv_central(&F, Xi, 1e-6, &dYi, &dError);
		dYt.push_back(dYi);

		if(lOneOnly) {
			lOneOnly = false;
			Ymin = Yi;
			Ymax = Yi;
		}

		if(Yi < Ymin) {Ymin = Yi;}
		if(Yi > Ymax) {Ymax = Yi;}
	}

	QCustomPlot* lCustomPlot = new QCustomPlot;

	lCustomPlot->addGraph();
	lCustomPlot->addGraph();

	lCustomPlot->graph(0)->setPen(QPen(QColor(0, 0, 255), 1, Qt::SolidLine));
	lCustomPlot->graph(1)->setPen(QPen(QColor(255, 0, 0), 1, Qt::SolidLine));

	lCustomPlot->graph(0)->setData(Xt, Yt);
	lCustomPlot->graph(1)->setData(Xt, dYt);

	lCustomPlot->xAxis->setLabel("x");
	lCustomPlot->yAxis->setLabel("y");
	lCustomPlot->xAxis->setRange(Xmin, Xmax);
	lCustomPlot->yAxis->setRange(Ymin, Ymax);
	lCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addWidget(lCustomPlot);

	setLayout(lMainLayout);
}
//===============================================
GDifferentiation::~GDifferentiation() {

}
//===============================================
void GDifferentiation::resize() {
	QFrame::resize(500, 300);
}
//===============================================
double GDifferentiation::onFunction(double x, void* params) {
	double y = x*x;
	return y;
}
//===============================================
