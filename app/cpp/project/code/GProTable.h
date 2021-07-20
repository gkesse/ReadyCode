//===============================================
#ifndef _GProTable_
#define _GProTable_
//===============================================
#include "GProUi.h"
//===============================================
class GProTable : public GProUi {
    Q_OBJECT
    
public:
    GProTable(QWidget* parent = 0);
    ~GProTable();
    void loadData(QStringList headers, QVector<QVector<QString>> datas);

public slots:
    void onEvent(int row, int col);

private:
	QTableWidget* m_tableWidget;
};
//==============================================
#endif
//==============================================
