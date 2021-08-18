//===============================================
#include "GCircuitRC.h"
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
	for(int i= 0; i < 101; i++) {
		double Xi = i/50.0 - 1;
		double Yi =Xi*Xi;
		m_xData.push_back(Xi);
		m_yData.push_back(Yi);
	}

    m_plot->addGraph();
    m_plot->graph(0)->setData(m_xData, m_yData);
    m_plot->xAxis->setLabel("x");
    m_plot->yAxis->setLabel("y");
    m_plot->xAxis->setRange(-1, 1);
    m_plot->yAxis->setRange(0, 1);
}
//===============================================
