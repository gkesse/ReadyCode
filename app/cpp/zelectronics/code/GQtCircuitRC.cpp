//===============================================
#include "GQtCircuitRC.h"
//===============================================
GQtCircuitRC::GQtCircuitRC(QWidget* parent) :
GQtUi(parent) {
	QCustomPlot* lCustomPlot = new QCustomPlot;

	lCustomPlot->addGraph();
	lCustomPlot->addGraph();

	lCustomPlot->graph(0)->setPen(QPen(QColor("teal"), 1.5));
	lCustomPlot->graph(0)->setName("Vc");

	lCustomPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
	lCustomPlot->graph(1)->setPen(QPen(QColor(120, 120, 120), 2));

	compute();

	lCustomPlot->xAxis2->setVisible(true);
	lCustomPlot->xAxis2->setTickLabels(false);
	lCustomPlot->yAxis2->setVisible(true);
	lCustomPlot->yAxis2->setTickLabels(false);

	lCustomPlot->graph(0)->setData(m_T, m_Vc);

	lCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	lCustomPlot->xAxis->setRange(m_Tmin - m_dT, m_Tmax + m_dT);
	lCustomPlot->yAxis->setRange(m_Vmin - m_dV, m_Vmax + m_dV);
	lCustomPlot->legend->setVisible(true);
	lCustomPlot->legend->setFont(QFont("Helvetica", 9));
	lCustomPlot->legend->setRowSpacing(-3);

	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addWidget(lCustomPlot);
	lMainLayout->setMargin(0);

	setLayout(lMainLayout);

	connect(lCustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), lCustomPlot->xAxis2, SLOT(setRange(QCPRange)));
	connect(lCustomPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), lCustomPlot->yAxis2, SLOT(setRange(QCPRange)));
}
//===============================================
GQtCircuitRC::~GQtCircuitRC() {

}
//===============================================
void GQtCircuitRC::resize() {
	QWidget::resize(400, 300);
}
//===============================================
void GQtCircuitRC::compute() {
	double Tmin = 0;
	double Tmax = 10e-3;
	double Nmax = 101;
	double dT = (Tmax - Tmin) / (Nmax - 1);
	double Ve = 5;
	double Ro = 1e3;
	double Co = 1e-6;
	double Tau = Ro*Co;
	double Vmin;
	double Vmax;
	bool lOneOnly = true;

	for(double Ti = Tmin; Ti <= Tmax; Ti += dT) {
		double Vc = Ve*(1 - qExp(-Ti/Tau));
		if(lOneOnly) {lOneOnly = false; Vmin = Vc; Vmax = Vc;}
		if(Vc < Vmin) {Vmin = Vc;}
		if(Vc > Vmax) {Vmax = Vc;}
		m_T.push_back(Ti);
		m_Vc.push_back(Vc);
	}

	m_Tmin = Tmin;
	m_Tmax = Tmax;
	m_Vmin = Vmin;
	m_Vmax = Vmax;
	m_dT = (m_Tmax - m_Tmin) / 50;
	m_dV = (m_Vmax - m_Vmin) / 50;
}
//===============================================
