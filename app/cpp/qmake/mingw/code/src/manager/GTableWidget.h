//===============================================
#ifndef _GTableWidget_
#define _GTableWidget_
//===============================================
#include "GObject.h"
//===============================================
class QTableWidget;
//===============================================
class GTableWidget : public GObject {
    Q_OBJECT

public:
    GTableWidget(QObject* _parent = 0);
    GTableWidget(int _rows, int _cols, QTableWidget* _tableWidget, QObject* _parent = 0);
    ~GTableWidget();
    void setSize();
    void addData(const QString& _data);

private:
    QTableWidget* m_tableWidget;
    int m_rows;
    int m_cols;
    int m_index;
};
//==============================================
#endif
//==============================================
