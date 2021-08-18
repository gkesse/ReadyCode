//===============================================
#include "GCircuitRC.h"
//===============================================
GCircuitRC::GCircuitRC(QWidget* parent) :
GElectronicsUi(parent) {
	QCustomPlot* lPlot = new QCustomPlot;

	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addWidget(lPlot);

	setLayout(lMainLayout);
}
//===============================================
GCircuitRC::~GCircuitRC() {

}
//===============================================
