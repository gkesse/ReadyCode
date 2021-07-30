//===============================================
#ifndef _GQtCircuitRC_
#define _GQtCircuitRC_
//===============================================
#include "GInclude.h"
#include "GQtUi.h"
//===============================================
class GQtCircuitRC : public GQtUi {
	Q_OBJECT

public:
	GQtCircuitRC(QWidget* parent = 0);
	~GQtCircuitRC();
	void resize();
	void compute();

private:
	QVector<double> m_T;
	QVector<double> m_Vc;
	double m_Tmin;
	double m_Tmax;
	double m_Vmin;
	double m_Vmax;
	double m_dT;
	double m_dV;
};
//==============================================
#endif
//==============================================
