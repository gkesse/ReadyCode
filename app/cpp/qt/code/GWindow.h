//================================================
#ifndef _GWindow_
#define _GWindow_
//================================================
#include <QApplication>
#include <QtWidgets>
#include <qcustomplot.h>
//================================================
class GWindow : public QFrame {
    Q_OBJECT
    
public:
    GWindow(QWidget* parent = 0);
    ~GWindow();
    
public:
    void onEvent(const QString& event);
    void detectPoint();
    
public slots:
    void slotMousePress(QMouseEvent* event);
    void slotMouseMove(QMouseEvent* event);

private:
    QCustomPlot* customPlot;
    double m_x;
    double m_y;
    double m_xmin;
    double m_xmax;
    double m_ymin;
    double m_ymax;
    int m_iClear;
    QVector<double> m_xData;
    QVector<double> m_yData;
    QCPItemText* m_coords;
    bool m_clearFlag;
};
//================================================
#endif
//================================================