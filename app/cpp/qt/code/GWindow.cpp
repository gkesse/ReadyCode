//================================================
#include "GWindow.h"
//================================================
GWindow::GWindow(QWidget* parent) : QFrame(parent) {
    customPlot = new QCustomPlot;

    m_xmin = -10.1; m_xmax = 10.1; m_ymin = -10.1; m_ymax = 10.1;
    
    customPlot->addGraph();
    customPlot->addGraph();
    customPlot->addGraph();
    customPlot->addGraph();
    
    customPlot->graph(0)->setPen(QPen(Qt::red));
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));    
    customPlot->graph(1)->setPen(QPen(Qt::blue));
    customPlot->graph(2)->setPen(QPen(Qt::NoPen));
    customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::gray, 1.5), QBrush(Qt::NoBrush), 16));    
    customPlot->graph(3)->setPen(QPen(Qt::NoPen));
    customPlot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::blue, 3), QBrush(Qt::NoBrush), 9));    
    
    m_coords = new QCPItemText(customPlot);
    m_coords->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_coords->position->setType(QCPItemPosition::ptPlotCoords);
    m_coords->setFont(QFont(font().family(), 10));
    m_coords->setPen(QPen(Qt::NoPen)); 
    m_coords->setText("");
    
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(m_xmin, m_xmax);
    customPlot->yAxis->setRange(m_ymin, m_ymax);

    m_clearFlag = false;

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(customPlot);

    setLayout(lMainLayout);
    
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(slotMousePress(QMouseEvent*)));
    connect(customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(slotMouseMove(QMouseEvent*)));
}
//================================================
GWindow::~GWindow() {

}
//================================================
void GWindow::onEvent(const QString& event) {
    if(event == "add_point") {
        m_xData << m_x;
        m_yData << m_y;
        customPlot->graph(0)->setData(m_xData, m_yData);
        customPlot->replot();
    }
    else if(event == "clear_point") {
        if(m_clearFlag == false) {return;}
        m_xData.removeAt(m_iClear);
        m_yData.removeAt(m_iClear);
        customPlot->graph(0)->setData(m_xData, m_yData);
        customPlot->graph(3)->setData({}, {});
        customPlot->replot();
    }
    else if(event == "mouse_move") {
        m_clearFlag = false;
        m_coords->position->setCoords(m_x, m_y + 2.5);
        customPlot->graph(3)->setData({}, {});
        detectPoint();
        m_coords->setText(QString("(%1 ; %2)").arg(m_x, 0, 'g', 2).arg(m_y, 0, 'g', 2));
        customPlot->graph(2)->setData({m_x}, {m_y});
        customPlot->replot();
    }
}
//================================================
void GWindow::detectPoint() {
    for(int i = 0; i < m_xData.size(); i++) {
        double lX = m_xData.at(i);
        double lY = m_yData.at(i);
        double dX = lX - m_x;
        double dY = lY - m_y;
        double dR = qSqrt(dX*dX + dY*dY);
        if(dR <= 0.1) {
            m_iClear = i;
            customPlot->graph(3)->setData({lX}, {lY});
            customPlot->replot();
            m_clearFlag = true;
            break;
        }
    }
}
//================================================
void GWindow::slotMousePress(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        m_x = customPlot->xAxis->pixelToCoord(event->pos().x());
        m_y = customPlot->yAxis->pixelToCoord(event->pos().y());
        onEvent("add_point");
    }
    else if(event->button() == Qt::RightButton) {
        onEvent("clear_point");
    }
}
//================================================
void GWindow::slotMouseMove(QMouseEvent* event) {
    m_x = customPlot->xAxis->pixelToCoord(event->pos().x());
    m_y = customPlot->yAxis->pixelToCoord(event->pos().y());
    onEvent("mouse_move");
}
//================================================
