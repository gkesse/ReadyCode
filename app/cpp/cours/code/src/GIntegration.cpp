//===============================================
#include "GIntegration.h"
//===============================================
GIntegration::GIntegration(QWidget* parent) : GGslUi(parent) {
    gsl_integration_workspace* Ws = gsl_integration_workspace_alloc (1000);

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
        double sYi, dError;
        double Yi = onFunction(Xi, 0);
        Xt.push_back(Xi);
        Yt.push_back(Yi);
        gsl_integration_qags (&F, 0, Xi, 0, 1e-7, 1000, Ws, &sYi, &dError);
        dYt.push_back(sYi);

        if(lOneOnly) {
            lOneOnly = false;
            Ymin = sYi;
            Ymax = sYi;
        }

        if(sYi < Ymin) {Ymin = sYi;}
        if(sYi > Ymax) {Ymax = sYi;}
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

    gsl_integration_workspace_free (Ws);
}
//===============================================
GIntegration::~GIntegration() {

}
//===============================================
void GIntegration::resize() {
    QFrame::resize(500, 300);
}
//===============================================
double GIntegration::onFunction(double x, void* params) {
    double y = x;
    return y;
}
//===============================================
